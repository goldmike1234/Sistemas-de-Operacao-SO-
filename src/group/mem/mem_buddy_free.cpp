/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //
    void deallocateHelper(MemTreeNode *node, Address address);

    void memBuddySystemFree(Address address)
    {
        soProbe(509, "%s(%u)\n", __func__, address);

        /* TODO POINT: Replace next instruction with your code */

        deallocateHelper(memTreeRoot, address);
    }

    void deallocateHelper(MemTreeNode *node, Address address) {
    if (node == NULL) {
        return;
    } else if (node->state == OCCUPIED && node->block.address == address) {
        node->state = FREE;
        node->block.pid = 0;
        return;
    } else if (node->state == SPLITTED) {
        deallocateHelper(node->left, address);
        deallocateHelper(node->right, address);
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

// ================================================================================== //

} // end of namespace group

