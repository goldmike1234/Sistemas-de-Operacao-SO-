/*
 *  \author Antonio Almeida (108250) & Pedro Torres (108799)
 */

#include "somm23.h"

namespace group
{

    // ================================================================================== //

    void swpRemove(uint32_t idx)
    {

        soProbe(406, "%s(%u)\n", __func__, idx);
        if (idx == 0)
        {
            swpHead = swpHead->next;
        }
        else
        {
            SwpNode *initial = swpHead;
            SwpNode *last = swpHead;

            for (uint32_t i = 0; i < idx; i++)
            {
                last = swpHead;

                if (swpHead == NULL)
                {
                    swpHead = initial;
                    throw Exception(EINVAL, __func__);
                }
                swpHead = swpHead->next;
            }
            last->next = swpHead->next;
            swpHead = initial;
        }

        /* TODO POINT: Replace next instruction with your code */
        // throw Exception(ENOSYS, __func__);
    }

    // ================================================================================== //

} // end of namespace group
