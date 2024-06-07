#include "somm23.h"
#include <unistd.h>

namespace group {

    void simRandomFill(uint32_t n, uint32_t seed) {
        soProbe(105, "%s(%u, %u)\\n", __func__, n, seed);

        require(n == 0 or n >= 2, "At least 2 processes are required");
        require(n <= MAX_PROCESSES, "More than MAX_PROCESSES processes are not allowed");

        if (n == 0) {
            n = rand() % (MAX_PROCESSES - 1) + 2;
        } 
        if (seed == 0) {
            seed = getpid();
        }

        srand(seed);

        u_int32_t arrivalTime = 0;
        for(int i = 0; i < n; i++) {
            uint32_t pid = rand() % 65535 + 1;
            int aux = 1;
            while (!aux) {
                aux = 1;
                for (uint32_t k = 0; k < i; k++) {
                    if (forthcomingTable.process[k].pid == pid) {
                        aux = 0;
                        pid = rand() % 65535 + 1;
                    }
                }
            }
            forthcomingTable.process[i].pid = pid;
            arrivalTime += rand() % 101;
            forthcomingTable.process[i].arrivalTime = arrivalTime;
            forthcomingTable.process[i].lifetime = rand() % 991 + 10;
            forthcomingTable.process[i].addressSpace.segmentCount = rand() % (MAX_SEGMENTS + 1);
            
            for (uint32_t j = 0; j < forthcomingTable.process[i].addressSpace.segmentCount; ++j){
                forthcomingTable.process[i].addressSpace.size[j] = rand() % 0x701 + 0x100;
            }

            feqInsert(ARRIVAL, arrivalTime, pid);

            forthcomingTable.count++;
        }
    }

 // end of namespace group
}