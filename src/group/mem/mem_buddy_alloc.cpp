/*
 *  \author Tomás Laranjo (107542)
 */

#include "somm23.h"

#include <stdint.h>



namespace group 
{

// ================================================================================== //

    Address allocateHelper(MemTreeNode *node, uint32_t pid, uint32_t size);

    Address memBuddySystemAlloc(uint32_t pid, uint32_t size) {
        require(pid > 0, "a valid process ID must be greater than zero");
        require(size > 0, "the size of a memory segment must be greater than zero");

        return allocateHelper(memTreeRoot, pid, size);
    }

    Address allocateHelper(MemTreeNode *node, uint32_t pid, uint32_t size) {
        if (node == NULL) {
            return NULL_ADDRESS;
        } else if (node->state == FREE && node->block.size >= size) {
            if (node->block.size / 2 >= size) { 
                node->state = SPLITTED;
                node->left = new MemTreeNode;
                node->right = new MemTreeNode;
                node->left->block.size = node->block.size / 2;
                node->right->block.size = node->block.size / 2;
                node->left->state = FREE;
                node->right->state = FREE;
                node->left->block.address = node->block.address;
                node->right->block.address = node->block.address + node->block.size / 2;
                node->left->block.pid = 0;
                node->right->block.pid = 0;
                return allocateHelper(node->left, pid, size); 
            }
            node->state = OCCUPIED;
            node->block.pid = pid;
            return node->block.address;
        } else if (node->state == OCCUPIED || node->block.size < size) {
            return NULL_ADDRESS;
        } else {
            Address leftAddress = allocateHelper(node->left, pid, size);
            if (leftAddress != NULL_ADDRESS) {
                return leftAddress;
            } else {
                return allocateHelper(node->right, pid, size);
            }
        }
    }
// ================================================================================== //

} // end of namespace group

