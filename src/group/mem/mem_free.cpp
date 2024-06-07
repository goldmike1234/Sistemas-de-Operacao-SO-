/*
 *  \author Antonio Almeida (108250) (Things related to First Fit)
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void memFree(AddressSpaceMapping *mapping)
    {
        soProbe(507, "%s(mapping: %p)\n", __func__, mapping);

        require(mapping != NULL, "mapping must be a valid pointer to a AddressSpaceMapping");

        /* TODO POINT: Replace next instruction with your code */
        if(memParameters.policy == FirstFit){
            for (int i =0;i < mapping->blockCount; i++){
                memFirstFitFree(mapping->address[i]);
            }

        } else {
            for (int i = 0;i < mapping->blockCount; i++){
                memBuddySystemFree(mapping->address[i]);
            }

        }
        
        //throw Exception(ENOSYS, __func__);
    }

// ================================================================================== //   
} // end of namespace group

