/*
 *  \author Aoki 108579
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void simRun(uint32_t cnt)
    {
        soProbe(108, "%s(%u)\n", __func__, cnt);

        /* TODO POINT: Replace next instruction with your code */
        try {
            // If the given number of steps is zero, the simulation must run til the end.
            if (cnt == 0) {
                while (true)
                    simStep();
            } else {
                // The simulation can reach the end in less than the given number of steps.
                for (uint32_t i = 0; i < cnt; ++i)
                    simStep();
            }
        } catch (Exception &e){
            throw e;
        }
    }

// ================================================================================== //

} // end of namespace group

