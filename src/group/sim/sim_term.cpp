/*
 *  \author Aoki 108579
 */

#include "somm23.h"

namespace group 
{

// ================================================================================== //

    void simTerm() 
    {
        soProbe(102, "%s()\n", __func__);

        feqTerm();
        memTerm();
        pctTerm();
        swpTerm();

        stepCount = 0;
        simTime = 0;
        forthcomingTable = ForthcomingTable();
    }

// ================================================================================== //

} // end of namespace group

