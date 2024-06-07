/*
 *  \author
 */

#include "somm23.h"
#include <cstring>
#include <cctype>

namespace group
{

    static char* clearStr(char* str);
    static void processLine(const char* line, ForthcomingProcess &fp);

// ================================================================================== //

    void simLoad(const char *fname)
    {
        soProbe(104, "%s(\"%s\")\n", __func__, fname);

        require(fname != NULL, "fname can not be a NULL pointer");
        require(forthcomingTable.count == 0, "Forthcoming table should be empty");


        FILE * f = fopen(fname, "r");
        if (f == NULL)
            throw Exception(ENOENT, __func__);

        size_t len = 0;
        char * line = NULL;
        ssize_t read;

        while ((read = getline(&line, &len, f)) != -1) {
            char* sanitizedLine = clearStr(line);

            if (*sanitizedLine == '%') continue;
            if  (*sanitizedLine == '\0') continue;

            ForthcomingProcess fp{};
            processLine(sanitizedLine, fp);
            forthcomingTable.process[forthcomingTable.count++] = fp;
        }

        fclose(f);
        if (line) free(line);
    }

// ================================================================================== //

    static char* clearStr(char* str) {
        if (str == NULL || *str == '\0') {
            return str;
        }

        char* start = str;
        char* end = str + strlen(str) - 1;

        while (isspace((unsigned char)*start)) {
            start++;
        }

        if (*start == '\0') {
            *str = '\0';
            return str;
        }

        while (end > start && isspace((unsigned char)*end)) {
            end--;
        }

        const size_t length = end - start + 1;
        memmove(str, start, length);
        str[length] = '\0';

        return str;
    }

    static void processLine(const char* line, ForthcomingProcess &fp) {
        uint32_t pid;
        uint32_t lifetime;
        uint32_t arrivalTime;

        char *addressSpaceStr = NULL;
        if (sscanf(
            line,
            " %u ; %u ; %u ; %m[^\n]",
            &pid,
            &arrivalTime,
            &lifetime,
            &addressSpaceStr
        ) < 4) {
            free(addressSpaceStr);
            throw Exception(EINVAL, __func__);
        }
        for (uint32_t i = 0; i < forthcomingTable.count; i++) {
            if (forthcomingTable.process[i].pid == pid) {
                free(addressSpaceStr);
                throw Exception(EINVAL, __func__);
            }
        }
        if (forthcomingTable.count > 0 && arrivalTime < forthcomingTable.process[forthcomingTable.count - 1].arrivalTime) {
            free(addressSpaceStr);
            throw Exception(EINVAL, __func__);
        }
        if (lifetime <= 0) {
            free(addressSpaceStr);
            throw Exception(EINVAL, __func__);
        }

        AddressSpaceProfile addressSpace{};
        addressSpace.segmentCount = 0;

        char *t = strtok(addressSpaceStr, ",");
        while (t) {
            addressSpace.size[addressSpace.segmentCount++] = atoi(clearStr(t));
            t = strtok(NULL, ",");
        }

        free(addressSpaceStr);

        fp.pid = pid;
        fp.arrivalTime = arrivalTime;
        fp.lifetime = lifetime;
        fp.addressSpace = addressSpace;

        feqInsert(ARRIVAL, fp.arrivalTime, fp.pid);
    }

} // end of namespace group
