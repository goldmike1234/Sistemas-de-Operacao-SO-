/*
 *  \author Antonio Almeida (108250) & Pedro Torres (108799)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    SwappedProcess *swpPeek(uint32_t idx)
    {
        soProbe(405, "%s(%u)\n", __func__, idx);

        /* TODO POINT: Replace next instruction with your code */
        SwpNode *initial = swpHead;
        // printf("%d \n", idx);
        // printf("%p \n", &swpHead->next);
        for(uint32_t i = 0; i<idx; i++){
            if (swpHead == NULL){
                swpHead = initial;
                return NULL;
            }
            // printf("--------------------\n");
            // printf(" I: %d \n", i);
            // printf("SWP : %p \n",&swpHead->next);
            swpHead = swpHead->next;
            // printf("SWP : %p \n",&swpHead->next);
            // printf("--------------------\n");
            
        }
        SwpNode * return_value = swpHead;
        swpHead = initial;
        return &return_value->process;
        //throw Exception(ENOSYS, __func__);
    }

// ================================================================================== //

} // end of namespace group