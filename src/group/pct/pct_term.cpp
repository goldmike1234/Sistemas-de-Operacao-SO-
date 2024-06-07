/*
 *  \author ...
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void pctTerm() 
    {
        soProbe(302, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        
        //Reset the internal data structure of the PCT module to the initial state.
        //The dynamic memory used by the module's linked list must be released and the supporting data structure reset to the initial state.

        PctNode *current = pctHead;
        PctNode *next = NULL;

        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }

        pctHead = NULL;
    }

// ================================================================================== //

} // end of namespace group

