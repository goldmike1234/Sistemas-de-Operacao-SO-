/*
 *  \author Antonio Almeida (108250) & Pedro Torres (108799)
 */

#include "somm23.h"
// ================================================================================== //
namespace group
{
    void swpAdd(uint32_t pid, AddressSpaceProfile *profile)
    {
        soProbe(404, "%s(%u, %p)\n", __func__, pid, profile);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(profile != NULL, "profile must be a valid pointer to a AddressSpaceProfile");

        // i need to check if the pid already exists in the linked list and also check if both the head and tail are null
        // if both are null, then i need to create a new node and set that node as the new tail and head
        // if both are not null, then i need to create a new node and set that node as the new tail

        // if the pid already exists in the linked list, then i need to update the profile of that node
        if (swpHead == NULL)
        {
            // First append
            swpHead = (SwpNode *)malloc((sizeof(SwpNode)));
            swpHead->process.pid = pid;
            swpHead->process.profile = *profile;
            swpHead->next = NULL;
            swpTail = swpHead;
        }
        else
        {
            // second append
            if (swpTail == swpHead)
            {
                swpTail = (SwpNode *)malloc((sizeof(SwpNode)));
                swpTail->process.pid = pid;
                swpTail->process.profile = *profile;
                swpTail->next = NULL;
                swpHead->next = swpTail;
            }
            else
            {
                SwpNode *node = (SwpNode *)malloc((sizeof(SwpNode)));
                node->process.pid = pid;
                node->process.profile = *profile;
                node->next = NULL;
                swpTail->next = node;
                swpTail = swpTail->next;
            }

        }
    }
} // end of namespace group
  // ================================================================================== //