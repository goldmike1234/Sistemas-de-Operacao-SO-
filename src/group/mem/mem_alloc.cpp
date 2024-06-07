/*
 *  \author Antonio Almeida (108250) (Things related to First Fit)
 *  \author Tomás Laranjo (107542) (Things related to Buddy System)
 */

#include "somm23.h"

#include <stdint.h>

namespace group
{

    // ================================================================================== //

    AddressSpaceMapping *memAlloc(uint32_t pid, AddressSpaceProfile *profile)
    {
        soProbe(504, "%s(%u, %p)\n", __func__, pid, profile);

        require(pid > 0, "process ID must be non-zero");
        require(profile != NULL, "profile must be a valid pointer to an AddressSpaceProfile variable");

        /* The mapping to be filled and whose pointer should be returned */
        static AddressSpaceMapping theMapping = {0, {0}};
        AddressSpaceMapping *return_value; 
        

        int size;
        int new_size [profile->segmentCount]; 
        for (int i = 0; i < profile->segmentCount; i++)
        {
            size = ((profile->size[i] + memParameters.chunkSize - 1) / memParameters.chunkSize) * memParameters.chunkSize;
            
            new_size[i] = size;
        }

        int needed_size = 0;
        int total_availablee_size = 0;
        for (int i = 0; i < profile->segmentCount; i++)
        {
            needed_size += new_size[i];
        }

        if (memParameters.policy == FirstFit)
        {
            total_availablee_size = memParameters.totalSize - memParameters.kernelSize;
        }
        else if (memParameters.policy == BuddySystem)
        {
            total_availablee_size = memParameters.totalSize - memParameters.kernelSize;
        }
        else
        {
            return IMPOSSIBLE_MAPPING;
        }


        if (total_availablee_size < needed_size)
        {
            return IMPOSSIBLE_MAPPING;
        }
        else
        {
            int addrs = 0;
            if (memParameters.policy == FirstFit)
            {
                int count;
                for (count = 0; count < profile->segmentCount; count++)
                {
                    addrs = memFirstFitAlloc(pid,new_size[count]);
                    if (addrs == 0){
                        break;
                    }
                    theMapping.address[count] =addrs;
                }
                if(count == profile->segmentCount){
                    theMapping.blockCount = count;
                    return_value = &theMapping;
                }
                else{
                    for(int i = 0; i< count; i++){
                        memFirstFitFree(theMapping.address[i]);
                    }
                    return_value = 0x0;
                }
            }
            else if (memParameters.policy == BuddySystem)// Buddy System
            {
                int counter;
                for (counter = 0; counter < profile->segmentCount; counter++)
                {
                    addrs = memBuddySystemAlloc(pid,new_size[counter]);
                    theMapping.address[counter] = addrs;
                    if (addrs == NULL_ADDRESS){
                        for(int i = 0; i < counter; i++){ 
                            memBuddySystemFree(theMapping.address[i]);
                            theMapping.address[i] = NULL_ADDRESS; // Reset the address
                        }
                        theMapping.blockCount = 0;
                        return_value = nullptr;
                        break;
                    }
                    theMapping.blockCount = counter + 1; 
                }
                if (counter == profile->segmentCount) {
                    return_value = &theMapping;
                }
            }
        }
        return return_value;


        //int counter;
        //        for (counter = 0; counter < profile->segmentCount; counter++)
        //        {
        //            addrs = memBuddySystemAlloc(pid,new_size[counter]);
        //            if (addrs == NULL_ADDRESS){
        //                break;
        //            }
        //            theMapping.address[counter] = addrs;
        //            theMapping.blockCount = counter + 1; 
        //        }
        //        if (counter == profile->segmentCount) {
        //            return_value = &theMapping;
        //        } else {
        //            // If allocation failed, free the blocks in reverse order
        //            for(int i = counter - 1; i >= 0; i--){ 
        //                memBuddySystemFree(theMapping.address[i]);
        //            }
        //            // Reset blockCount to reflect the number of successfully allocated blocks
        //            theMapping.blockCount = 0;
        //            return_value = nullptr;
        //        }


        // for (int i = 0; i < profile->segmentCount; i++)
        // {
        //     if (memParameters.policy == FirstFit)
        //     {
        //         if (profile->size[i] > memParameters.chunkSize)
        //         {
        //             // Round Up
        //             size = ((profile->size[i] + memParameters.chunkSize - 1) / memParameters.chunkSize) * memParameters.chunkSize;
        //         }
        //         else
        //         {
        //             // Not Round
        //             size = memParameters.chunkSize;
        //         }

        //         if (size > memParameters.totalSize)
        //         {
        //             // printf("AAAAAAAAAAAA \n");
        //             return IMPOSSIBLE_MAPPING;
        //         }

        //         theMapping.blockCount++;
        //         theMapping.address[i] = memFirstFitAlloc(pid, size);
        //         if (theMapping.address[i] == 0)
        //         {
        //             for (int x = 0; x < theMapping.blockCount - 1; x++)
        //             {
        //                 // printf("AAAAAAAAAAAAAAAAAAAAAAAA: %x \n",theMapping.address[x]);
        //                 memFirstFitFree(theMapping.address[x]);
        //             }
        //             return NO_MAPPING;
        //         }
        //     }
        //     else // Buddy System
        //     {
        //         theMapping.address[i] = memBuddySystemAlloc(pid, profile->size[i]);
        //         if (theMapping.address[i] == NULL_ADDRESS)
        //         {
        //             for (int x = 0; x < i; x++)
        //             {
        //                 memBuddySystemFree(theMapping.address[x]);
        //             }
        //             // Reset blockCount and addresses in theMapping after a failed allocation
        //             theMapping.blockCount = 0;
        //             for (int x = 0; x < MAX_SEGMENTS; x++)
        //             {
        //                 theMapping.address[x] = NULL;
        //             }
        //             return NO_MAPPING;
        //         }
        //         else
        //         {
        //             theMapping.blockCount++;
        //         }
        //     }
        // }

        // for (int i = theMapping.blockCount; i < MAX_SEGMENTS; i++)
        // {
        //     theMapping.address[i] = NULL;
        // }

        // return &theMapping;
    }
    // ================================================================================== //

} // end of namespace group
