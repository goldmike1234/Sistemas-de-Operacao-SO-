/*
 *  \author Antonio Almeida (108250)
 */

#include "somm23.h"

#include <stdint.h>

namespace group
{

    // ================================================================================== //
    void memFirstFitFree(Address address)
    {
        soProbe(508, "%s(%u)\n", __func__, address);

        require(memOccupiedHead != NULL, "Occupied list should contain nodes");

        Address a;
        MemListNode *p_1 = NULL;
        MemListNode *p_2 = new MemListNode;
        MemListNode *p_cur;
        MemListNode *new_node;

        for (p_2 = memOccupiedHead; (p_cur = p_2, p_2 != NULL && address != p_2->block.address); p_2 = p_2->next)
        {
            p_1 = p_2;
        }
        if (p_1 == NULL)
        {
            memOccupiedHead = p_2->next;
        }
        else
        {
            p_1->next = p_2->next;
        }
        if (p_2->next != NULL)
        {
            p_2->next->prev = p_1;
        }
        p_2->block.pid = 0;
        p_2->next = NULL;
        p_2->prev = NULL;
        p_1 = NULL;
        for (p_2 = memFreeHead; (p_2 != NULL && p_2->block.address <= address); p_2 = p_2->next)
        {
            p_1 = p_2;
        }
        p_cur->next = p_2;
        p_cur->prev = p_1;
        if (p_1 == NULL)
        {
            memFreeHead = p_cur;
        }
        else
        {
            p_1->next = p_cur;
        }
        if (p_2 != NULL && (p_2->prev = p_cur, p_cur->block.address + p_cur->block.size == p_2->block.address))
        {
            p_cur->block.size = p_cur->block.size + p_2->block.size;
            p_cur->next = p_2->next;
            if (p_2 != NULL)
            {
                delete (p_2);
            }
        }
        if (p_1 != NULL && (p_1->block.address + p_1->block.size == p_cur->block.address))
        {
            p_1->block.size = p_1->block.size + p_cur->block.size;
            p_1->next = p_cur->next;
            if (p_cur != NULL)
            {
                delete (p_cur);
            }
        }
        return;

    }

    // ================================================================================== //

} // end of namespace group
