/*
 *  \author Michael Cerqueira (108732)
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void memFreeAll(MemTreeNode *node) {
        if (node == NULL) {
            return;
        } else if (node->state == OCCUPIED) {
            node->state = FREE;
            node->block.pid = 0;
            return;
        } else if (node->state == SPLITTED) {
            memFreeAll(node->left);
            memFreeAll(node->right);
            // Merge adjacent free blocks if both children are free
            if (node->left->state == FREE && node->right->state == FREE) {
                node->state = FREE;
                node->block.pid = 0;
                delete node->left;
                delete node->right;
                node->left = NULL;
                node->right = NULL;
            }
        }
    }

    void memTerm() 
    {
        soProbe(502, "%s()\n", __func__);

        /* TODO POINT: Replace next instruction with your code */
        if (memParameters.policy == FirstFit) {
            while (memFreeHead != NULL) {
                MemListNode *aux = memFreeHead;
                memFreeHead = memFreeHead->next;
                delete aux;
            }
            while (memOccupiedHead != NULL) {
                MemListNode *aux = memOccupiedHead;
                memOccupiedHead = memOccupiedHead->next;
                delete aux;
            }
        } else {
            while (memTreeRoot != NULL) {
                memFreeAll(memTreeRoot); // go thru all nodes and delete them
                delete memTreeRoot;
                memTreeRoot = NULL;
            }
        }

    }

// ================================================================================== //

} // end of namespace group

