/*
 *  \author Anderson Aoki (108579) & Michael Cerqueira (108732)
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void feqInsert(FutureEventType type, uint32_t time, uint32_t pid)
    {
        const char *tas = type == ARRIVAL ? "ARRIVAL" : type == TERMINATE ? "TERMINATE" : "UNKOWN";
        soProbe(204, "%s(%s, %u, %u)\n", __func__, tas, time, pid);

        require(pid > 0, "process ID must be non-zero");

        /* TODO POINT: Replace next instruction with your code */
        FeqEventNode *newNode = new FeqEventNode;
        newNode->event.type = type;
        newNode->event.time = time;
        newNode->event.pid = pid;
        newNode->next = NULL;

        if(feqHead == NULL) {
            feqHead = newNode;
            return;
        }
        
        FeqEventNode *aux = feqHead;
        FeqEventNode *prev = NULL;

        while (aux != NULL) {
            if (aux->event.time > newNode->event.time) {
                if (prev == NULL) {
                    newNode->next = aux;
                    feqHead = newNode;
                } else {
                    prev->next = newNode;
                    newNode->next = aux;
                }
                return;
                
            } else if (aux->event.time == newNode->event.time) {
                if (newNode->event.type == TERMINATE && aux->event.type == ARRIVAL) {
                    if (prev == NULL) {
                        newNode->next = aux;
                        feqHead = newNode;
                    } else {
                        prev->next = newNode;
                        newNode->next = aux;
                    }
                    return;
                } else {
                    while (aux->next != NULL && aux->next->event.time == newNode->event.time) {
                        if (newNode->event.type == TERMINATE && aux->next->event.type == ARRIVAL) {
                            break;
                        }
                        aux = aux->next;
                    }
                    newNode->next = aux->next;
                    aux->next = newNode;
                    return;
                }
}
            prev = aux;
            aux = aux->next;
        }

        // If newNode should be inserted at the end of the list
        if (prev == NULL) {
            feqHead = newNode;
        } else {
            prev->next = newNode;
        }

    }


// ================================================================================== //

} // end of namespace group