/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void pctUpdateState(uint32_t pid, ProcessState state, uint32_t time = NO_TIME, AddressSpaceMapping *mapping = NULL)
    {
        soProbe(309, "%s(%d, %u, %u)\n", __func__, pid, state, time);

        require(pid > 0, "a valid process ID must be greater than zero");

        /* TODO POINT: Replace next instruction with your code */

        PctNode *current = pctHead;
        bool processFound = false;

        while (current != NULL)
        {
            if (current->pcb.pid == pid)
            {
                processFound = true;
                if (state == ProcessState::ACTIVE) {
                    current->pcb.state = ProcessState::ACTIVE;
                    current->pcb.activationTime = time;
                    current->pcb.memMapping = *mapping;
                } else if (state == ProcessState::FINISHED) {
                    current->pcb.state = ProcessState::FINISHED;
                    current->pcb.finishTime = time;
                } else if (state == ProcessState::SWAPPED or state == ProcessState::DISCARDED) {
                    current->pcb.state = state;
                }
            }
            current = current->next;
        }
        if (!processFound) {
            throw Exception(EINVAL, __func__);
        }
    }

// ================================================================================== //

} // end of namespace group

