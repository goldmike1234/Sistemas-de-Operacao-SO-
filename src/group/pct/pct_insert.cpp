/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void pctInsert(uint32_t pid, uint32_t time, uint32_t lifetime, AddressSpaceProfile *profile)
    {
        soProbe(304, "%s(%d, %u, %u, %p)\n", __func__, pid, time, lifetime, profile);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(time >= 0, "time must be >= 0");
        require(lifetime > 0, "lifetime must be > 0");
        require(profile != NULL, "profile must be a valid pointer to a AddressSpaceProfile");

        /* TODO POINT: Replace next instruction with your code */

        PctNode *newNode = new PctNode;
        newNode->pcb.pid = pid;
        newNode->pcb.state = NEW;
        newNode->pcb.arrivalTime = time;
        newNode->pcb.lifetime = lifetime;
        newNode->pcb.activationTime = NO_TIME;
        newNode->pcb.finishTime = NO_TIME;
        newNode->pcb.memProfile = *profile;

        if (pctHead == NULL) {
            pctHead = newNode;
        } else {
            PctNode *currentNode = pctHead;
            PctNode *previousNode = NULL;
            while (currentNode != NULL) {
                if (currentNode->pcb.pid == pid) {
                    throw Exception(EINVAL, __FUNCTION__);
                } else if (currentNode->pcb.pid > pid) {
                    if (previousNode == NULL) {
                        newNode->next = pctHead;
                        pctHead = newNode;
                    } else {
                        previousNode->next = newNode;
                        newNode->next = currentNode;
                    }
                    break;
                } else if (currentNode->next == NULL) {
                    currentNode->next = newNode;
                    break;
                }
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }
    }

// ================================================================================== //

} // end of namespace group

