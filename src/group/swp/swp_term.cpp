/*
 *  \author Antonio Almeida (108250) & Pedro Torres (108799)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void swpTerm()
    {
        soProbe(402, "%s()\n", __func__);

        SwpNode *current = swpHead;
        SwpNode *next = NULL;
        
        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }

        swpHead = NULL;
    }

// ================================================================================== //

} // end of namespace group

