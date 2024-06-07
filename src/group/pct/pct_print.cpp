/*
 *  \author ...
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void pctPrint(FILE *fout)
    {
        soProbe(303, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        /* TODO POINT: Replace next instruction with your code */

        //\param [in] pid Id of process associated to the new entry
        //\param [in] time Time at which the process is submitted (arrival)
        //\param [in] lifetime Time the process takes to run, after it is in main memory
        //\param [in] memProfile Process' address space profile

        try {
            PctNode *current = pctHead;
            fprintf(fout, "+====================================================================================================================================================+\n");
            fprintf(fout, "|                                                                  Process Control Table                                                             |\n");
            fprintf(fout, "+-------+-----------+---------+----------+---------+---------+---------------------------------------+-----------------------------------------------+\n");
            fprintf(fout, "|  PID  |   state   | arrival | lifetime | active  | finish  |         address space profile         |             address space mapping             |\n");
            fprintf(fout, "+-------+-----------+---------+----------+---------+---------+---------------------------------------+-----------------------------------------------+\n");
            while (current != NULL) {
                fprintf(fout, "|%6d |", current->pcb.pid);

                if (current->pcb.state == NEW) {
                    fprintf(fout, " %-9s |", "NEW");
                }
                else if (current->pcb.state == ACTIVE) {
                    fprintf(fout, " %-9s |", "ACTIVE");
                }
                else if (current->pcb.state == SWAPPED) {
                    fprintf(fout, " %-9s |", "SWAPPED");
                }
                else if (current->pcb.state == FINISHED) {
                    fprintf(fout, " %-9s |", "FINISHED");
                }
                else if (current->pcb.state == DISCARDED) {
                    fprintf(fout, " %-9s |", "DISCARDED");
                }
                else {
                    fprintf(fout, " %-9s |", "UNKNOWN");
                }
                
                fprintf(fout, "%8d |", current->pcb.arrivalTime);
                fprintf(fout, "%9u |", current->pcb.lifetime);

                if (current->pcb.activationTime == 0xFFFFFFFF) {
                    fprintf(fout, "%s|", "   ---   ");
                }
                else {
                    fprintf(fout, "%8d |", current->pcb.activationTime);
                }

                if (current->pcb.finishTime == 0xFFFFFFFF) {
                    fprintf(fout, "%s|", "   ---   ");
                }
                else {
                    fprintf(fout, "%8d |", current->pcb.finishTime);
                }

                for (int i = 0; i < MAX_BLOCKS; i++) {
                    if (current->pcb.memProfile.segmentCount <= (uint32_t) i) {
                        fprintf(fout, "%8s", "   ---   ");
                    } else {
                        fprintf(fout, "%8u ", current->pcb.memProfile.size[i]);
                    }
                    fprintf(fout, (i < MAX_BLOCKS - 1) ? ":" : "|");
                }

                for (int i = 0; i < MAX_BLOCKS; i++) {
                    if (current->pcb.memMapping.blockCount <= (uint32_t) i) {
                        fprintf(fout, "%8s", "    ---    ");
                    } else {
                        fprintf(fout, " 0x%07x ", current->pcb.memMapping.address[i]);
                    }
                    fprintf(fout, (i < MAX_BLOCKS - 1) ? ":" : "|\n");
                }
                current = current->next;
            }
                
            fprintf(fout, "+====================================================================================================================================================+\n");
            fprintf(fout, "\n");
        } catch (Exception &e) {
            throw e;
        }

    }

// ================================================================================== //

} // end of namespace group
