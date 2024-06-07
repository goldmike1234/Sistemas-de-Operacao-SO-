/*
 *  \author Anderson Aoki (108579) & Michael Cerqueira (108732)
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void feqPrint(FILE *fout)
    {
        soProbe(203, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        /* TODO POINT: Replace next instruction with your code */

        try {
            FeqEventNode *current = feqHead;
            fprintf(fout, "+==============================+\n");
            fprintf(fout, "|      Future Event Queue      |\n");
            fprintf(fout, "+----------+-----------+-------+\n");
            fprintf(fout, "|   time   |   type    |  PID  |\n");
            fprintf(fout, "+----------+-----------+-------+\n");
            while (current != NULL) {
                fprintf(fout, "|%9u |", current->event.time);
                if (current->event.type == ARRIVAL) {
                    fprintf(fout, "%8s   |", "ARRIVAL");

                } else if (current->event.type == TERMINATE) {

                    fprintf(fout, "%10s |", "TERMINATE");
                } else {
                    
                    fprintf(fout, "%10s |", "UNKNOWN");
                }

                fprintf(fout, "%6u |\n", current->event.pid);
                current = current->next;
            }
            fprintf(fout, "+==============================+\n\n");

        } catch (Exception &e) {
            throw e;
        }
    }
} // end of namespace group