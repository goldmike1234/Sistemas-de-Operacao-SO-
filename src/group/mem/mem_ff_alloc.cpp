/*
 *  \author Antonio Almeida (108250)
 */

#include "somm23.h"

#include <stdint.h>

namespace group
{

    // ================================================================================== //

    Address memFirstFitAlloc(uint32_t pid, uint32_t size)
    {
        soProbe(505, "%s(%u, %#x)\n", __func__, pid, size);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(size, "the size of a memory segment must be greater then zero");
        // printf("First time : %d | %d \n", memFreeHead->block.size, size);
        Address a;
        MemListNode *p_1 = NULL;
        MemListNode *p_2 = new MemListNode;
        MemListNode *p_cur;
        MemListNode *new_node;

        for (p_2 = memFreeHead; (p_2 != NULL && p_2->block.size < size); p_2 = p_2->next)
        {
            // printf("P2 Free: %x \n",p_2->block.address);
            p_1 = p_2;
        }

        if (p_2 == NULL)
        {
            a = 0;
        }
        else
        {
            if (size < p_2->block.size)
            {
                new_node = new MemListNode;
                new_node->block.address = p_2->block.address;
                new_node->block.size = size;
                p_2->block.address = p_2->block.address + size;
                p_2->block.size = p_2->block.size - size;
            }
            else
            {
                p_cur = p_2->next;
                if (p_1 != NULL)
                {
                    p_1->next = p_2->next;
                    p_cur = memFreeHead;
                }
                memFreeHead = p_cur;
                new_node = p_2;
            }

            new_node->block.pid = pid;
            p_1 = NULL;
            for (p_2 = memOccupiedHead; (p_2 != NULL && (p_2->block.address <= new_node->block.address)); p_2 = p_2->next)
            {
                // printf("P2 Occupied : %x \n",p_2->block.address);
                p_1 = p_2;
            }
            new_node->next = p_2;
            new_node->prev = p_1;
            if (p_1 == NULL)
            {
                memOccupiedHead = new_node;
            }
            else
            {
                p_1->next = new_node;
            }
            if (p_2 != NULL)
            {
                p_2->prev = new_node;
            }

            a = new_node->block.address;
        }
        return a;
    }
    // ================================================================================== //

} // end of namespace group
