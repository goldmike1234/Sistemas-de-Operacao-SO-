/*
 *  \author Antonio Almeida (108250) & Pedro Torres (108799)
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void swpPrint(FILE *fout)
    {
        soProbe(403, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        fprintf(fout,"+===============================================+\n");
        fprintf(fout,"|             Swapped Process Queue             |\n");
        fprintf(fout,"+-------+---------------------------------------+\n");
        fprintf(fout,"|  PID  |         address space profile         |\n");
        fprintf(fout,"+-------+---------------------------------------+\n");
        if (swpHead == NULL){   
            
        }else{

            SwpNode *init = swpHead;
            int value = 0;
            while (swpHead!= NULL)
            {

                fprintf(fout,"|%6d |",swpHead->process.pid); 
                value = 0;
                for (int i = 0; i<swpHead->process.profile.segmentCount; i++){
                    fprintf(fout,"  %6d :",swpHead->process.profile.size[i]);
                    value++;
                }
                for (value; value < 3; value++){
                    fprintf(fout,"%6s   :", "---");
                }

                fprintf(fout,"%6s   |\n","---");
                swpHead = swpHead->next;
            } 
            swpHead = init; 
        }
        
        fprintf(fout,"+===============================================+\n\n");
        //throw Exception(ENOSYS, __func__);
    }

// ================================================================================== //

} // end of namespace group
