/*
 *  \author Aoki 108579 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    // Global variables
    uint32_t memSize;
    uint32_t memSizeOS;
    uint32_t chunkSize;
    AllocationPolicy policy;

    /*
     * \brief Init the module's internal data structure
     */
    void simInit(uint32_t mSize, uint32_t osSize, uint32_t cSize, AllocationPolicy policy)
    {
        const char *pas = policy == FirstFit ? "FirstFit" : policy == BuddySystem ? "BuddySystem" : "Unkown";
        soProbe(101, "%s(%#x, %#x, %#x, %s)\n", __func__, mSize, osSize, cSize, pas);

        /* TODO POINT: Replace next instruction with your code */
        stepCount = 0;
        simTime = 0;
        forthcomingTable = ForthcomingTable();

        feqInit();
        memInit(mSize, osSize, cSize, policy);
        pctInit();
        swpInit();        
    }

// ================================================================================== //

} // end of namespace group

