/*
 *  \author Aoki 108579
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void simPrint(FILE *fout)
    {
        soProbe(103, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        /* TODO POINT: Replace next instruction with your code */

        try
        {
            fprintf(fout, "+====================================================================+\n");
            fprintf(fout, "|                          forthcomingTable                          |\n");
            fprintf(fout, "+-------+---------+----------+---------------------------------------+\n");
            fprintf(fout, "|    Simulation step: %6d |              Simulation time: %7d |\n", stepCount, simTime);
            fprintf(fout, "+-------+---------+----------+---------------------------------------+\n");
            fprintf(fout, "|  PID  | arrival | lifetime |         address space profile         |\n");
            fprintf(fout, "+-------+---------+----------+---------------------------------------+\n");

            for (uint32_t i = 0; i < forthcomingTable.count; ++i)
            {
                const auto& process = forthcomingTable.process[i];
                fprintf(fout, "| %5d | %7d | %8d |", process.pid, process.arrivalTime, process.lifetime);
                
                for (uint32_t j = 0; j < 4; ++j) {
                    if (j < process.addressSpace.segmentCount) {
                        fprintf(fout, "  %6u", process.addressSpace.size[j]);
                    } else {
                        fprintf(fout, "   ---  ");
                    }
                    if (j < 3) { // Only print colon if it's not the last segment
                        fprintf(fout, " :");
                    }
                }
                
                fprintf(fout, " |\n"); // Add spaces before the closing pipe
            }
            
            fprintf(fout, "+====================================================================+\n\n");
        
        } catch (Exception &e){
            throw e;
        }
    }

// ================================================================================== //

} // end of namespace group

