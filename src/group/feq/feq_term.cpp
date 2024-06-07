/*
 *  \author Anderson Aoki (108579) & Michael Cerqueira (108732)
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void feqTerm() 
    {
        soProbe(202, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */

        /*
        Reset the internal data structure of the FEQ module to the initial state.

        The dynamic memory used by the module's linked list must be released and 
        the supporting data structure reset to the initial state.
        */

        FeqEventNode *current = feqHead;
        FeqEventNode *next = NULL;
        
        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }

        feqHead = NULL;
    }

// ================================================================================== //

} // end of namespace group