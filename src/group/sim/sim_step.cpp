/*
 *  \author Aoki 108579
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    bool simStep()
    {
        soProbe(107, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        if (feqIsEmpty()) {
            return false;
        }

        FutureEvent event = feqPop();
        
        AddressSpaceMapping *map; // for ARRIVAL
        ForthcomingProcess *proc; // for ARRIVAL
        SwappedProcess *swp;      // for TERMINATE
        
        simTime = event.time;

        uint32_t pos;

        switch (event.type)
        {
            case ARRIVAL:
                proc = simGetProcess(event.pid);
                map = memAlloc(proc->pid, (AddressSpaceProfile*) &proc->addressSpace);

                pctInsert(proc->pid, proc->arrivalTime, proc->lifetime, (AddressSpaceProfile*) &proc->addressSpace);

                if (map == IMPOSSIBLE_MAPPING) {
                    pctUpdateState(proc->pid,DISCARDED,NO_TIME,NULL_ADDRESS);
                    simTime = proc->arrivalTime;
                    return true;
                }

                if (map == NO_MAPPING) {
                    swpAdd(proc->pid, (AddressSpaceProfile*) &proc->addressSpace);
                    pctUpdateState(proc->pid,SWAPPED,NO_TIME,NULL_ADDRESS);
                    simTime = proc->arrivalTime;
                    return true;

                } 

                feqInsert(TERMINATE, proc->lifetime + simTime, proc->pid);
                pctUpdateState(proc->pid, ACTIVE, simTime, map);

                simTime = proc->arrivalTime;             
                break;

            case TERMINATE:
                map = pctGetAddressSpaceMapping(event.pid);
                memFree(map);

                pctUpdateState(event.pid, FINISHED, event.time, NULL_ADDRESS);

                pos = 0;

                while (true) {
                    swp = swpPeek(pos);

                    if (swp == NULL_ADDRESS) {
                        break;
                    }

                    map = memAlloc(swp->pid, pctGetAddressSpaceProfile(swp->pid));
                    if (map == NO_MAPPING) {
                        pos++;
                        break;
                    }

                    feqInsert(TERMINATE, pctGetLifetime(swp->pid) + simTime, swp->pid);
                    pctUpdateState(swp->pid, ACTIVE, simTime, map);
                    swpRemove(pos);
                }
                break;
            
            default:
                throw Exception(ENOSYS, "Unknown event type");
        }

        stepCount++;
        return true;
    }

// ================================================================================== //

}
