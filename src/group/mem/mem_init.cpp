/*
 *  \author Antonio Almeida (108250) (Things related to First Fit)
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void memInit(uint32_t mSize, uint32_t osSize, uint32_t cSize, AllocationPolicy policy) 
    {
        const char *pas = policy == FirstFit ? "FirstFit" : policy == BuddySystem ? "BuddySystem" : "Unkown";
        soProbe(501, "%s(%#x, %#x, %#x, %s)\n", __func__, mSize, osSize, cSize, pas);

        require(mSize > osSize, "memory must be bigger than the one use by OS");
        require((mSize % cSize) == 0, "memory size must be a multiple of chunck size");
        require((osSize % cSize) == 0, "memory size for OS must be a multiple of chunck size");
        require(policy == FirstFit or policy == BuddySystem, "policy must be FirstFit or BuddySystem");

        memParameters.policy = policy;
        memParameters.chunkSize = cSize;
        memParameters.totalSize = mSize;
        memParameters.kernelSize = osSize;


        if (policy == FirstFit){
            memFreeHead = (MemListNode*) malloc(sizeof(MemListNode));
            memFreeHead->next = NULL;
            memFreeHead->prev = NULL;
            memFreeHead->block.address = osSize;
            memFreeHead->block.pid = 0;
            memFreeHead->block.size = mSize - osSize;
            memOccupiedHead = NULL;
            memTreeRoot = NULL;
            
        } else {
            memFreeHead = NULL;
            memOccupiedHead = NULL;
            memTreeRoot = (MemTreeNode*) malloc(sizeof(MemTreeNode));
            memTreeRoot->block.address = osSize;
            memTreeRoot->block.pid = 0;
            memTreeRoot->block.size = mSize / 2;
            memTreeRoot->left = NULL;
            memTreeRoot->right = NULL;
        }


    }

// ================================================================================== //

} // end of namespace group

