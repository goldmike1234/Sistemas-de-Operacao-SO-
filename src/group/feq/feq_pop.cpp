/*
 *  \author Anderson Aoki (108579) & Michael Cerqueira (108732)
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    FutureEvent feqPop()
    {
        soProbe(205, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        /*
        Remove and returns the first event from the list.

        The following must be considered:

            The event must be removed from the queue.
            The EINVAL exception should be thrown, if no event exists.
            All exceptions must be of the type defined in this project (Exception).

        */

        if (feqIsEmpty()) {
           throw Exception(EINVAL, "No event exists");
        }

        FutureEvent event;
        event.type = feqHead->event.type;
        event.time = feqHead->event.time;
        event.pid = feqHead->event.pid;

        FeqEventNode *oldHead = feqHead;
        feqHead = feqHead->next;

        delete oldHead;

        return event;
    }

// ================================================================================== //

    bool feqIsEmpty()
    {
        soProbe(206, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        // verify if the list is empty
        if (feqHead == NULL) {
            return true;
        } else {
            return false; }    // if feq head == null means there are no events in the list, otherwise there are events in the list
    }

// ================================================================================== //

} // end of namespace group