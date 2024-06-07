/*
 *  \author Michael Cerqueira (108732)
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //
    void traverseAndPrint(MemTreeNode *node, FILE *fout);
    void traverseAndPrintFree(MemTreeNode *node, FILE *fout);

    void memPrint(FILE *fout) {
        soProbe(503, "%s(\"%p\")\n", __func__, fout);

        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        /* TODO POINT: Replace next instruction with your code */
        if (memParameters.policy == FirstFit) {
            fprintf(fout, "+====================================+\n");
            fprintf(fout, "|   FirstFit memory occupied blocks  |\n");
            fprintf(fout, "+---------+-------------+------------+\n");
            fprintf(fout, "|   PID   |   address   |    size    |\n");
            fprintf(fout, "+---------+-------------+------------+\n");

            MemListNode *occupied = memOccupiedHead;

            while (occupied != NULL) {
                fprintf(fout, "| %7u | %#11x | %10u |\n", occupied->block.pid, occupied->block.address, occupied->block.size);
                occupied = occupied->next;
            }
            fprintf(fout, "+====================================+\n\n");

            fprintf(fout, "+====================================+\n");
            fprintf(fout, "|     FirstFit memory free blocks    |\n");
            fprintf(fout, "+---------+-------------+------------+\n");
            fprintf(fout, "|   PID   |   address   |    size    |\n");
            fprintf(fout, "+---------+-------------+------------+\n");

            MemListNode *free = memFreeHead;

            while (free != NULL) {
                fprintf(fout, "|   ---   | %#11x | %10u |\n", free->block.address, free->block.size);
                free = free->next;
            }

            fprintf(fout, "+====================================+\n\n");
        } else {
            fprintf(fout, "+====================================+\n");
            fprintf(fout, "| BuddySystem memory occupied blocks |\n");
            fprintf(fout, "+---------+-------------+------------+\n");
            fprintf(fout, "|   PID   |   address   |    size    |\n");
            fprintf(fout, "+---------+-------------+------------+\n");

            MemTreeNode *root = memTreeRoot;

            // Helper function to traverse the tree and print occupied blocks
            
            traverseAndPrint(root, fout);

            fprintf(fout, "+====================================+\n\n");

            fprintf(fout, "+====================================+\n");
            fprintf(fout, "|   BuddySystem memory free blocks   |\n");
            fprintf(fout, "+---------+-------------+------------+\n");
            fprintf(fout, "|   PID   |   address   |    size    |\n");
            fprintf(fout, "+---------+-------------+------------+\n");

            traverseAndPrintFree(root, fout);

            fprintf(fout, "+====================================+\n\n");
        }
            
    }

    void traverseAndPrint(MemTreeNode *node, FILE *fout) {
        if (node == NULL) {
            return;
        }
        if (node->state == OCCUPIED) {
            fprintf(fout, "| %7u | %#11x | %10u |\n", node->block.pid, node->block.address, node->block.size);
        }
        traverseAndPrint(node->left, fout);
        traverseAndPrint(node->right, fout);
    }

    void traverseAndPrintFree(MemTreeNode *node, FILE *fout) {
        if (node == NULL) {
            return;
        }
        if (node->state == FREE) {
            fprintf(fout, "|   ---   | %#11x | %10u |\n", node->block.address, node->block.size);
        }
        traverseAndPrintFree(node->left, fout);
        traverseAndPrintFree(node->right, fout);
    }


// ================================================================================== //

} // end of namespace group

