/*
 
\author Pedro Torres*/

#include "somm23.h"

namespace group
{

// ================================================================================== //

    ForthcomingProcess *simGetProcess(uint32_t pid)
    {
        soProbe(106, "%s(%u)\n", __func__, pid);
        require(pid > 0, "a valid process ID must be greater than zero");

        // Assuming 'forthcomingTable' is an array or collection of processes
        for (int i = 0; i < forthcomingTable.count; i++) {
            if (forthcomingTable.process[i].pid == pid) {
                return &forthcomingTable.process[i];
            }
        }
        throw Exception(EINVAL, __func__); // Process not found
    }

// ================================================================================== //

} // end of namespace group