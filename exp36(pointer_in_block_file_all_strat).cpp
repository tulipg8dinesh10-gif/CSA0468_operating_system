#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

// Structure to represent a block 
struct Block { 
    char data[256]; 
    struct Block* next; 
}; 

int main() { 
    struct Block* firstBlock = NULL; // Pointer to the first block in the linked list 
    struct Block* lastBlock = NULL;  // Pointer to the last block in the linked list 
    int blockCount = 0;              // Count of blocks in the linked list 
    int blockNumber; 
    char inputData[256]; 
    char choice; 

    printf("Linked Allocation Simulation\n"); 

    while (1) { 
        printf("\nEnter 'W' to write a block, 'R' to read a block, or 'Q' to quit: "); 
        scanf(" %c", &choice); 

        if (choice == 'Q' || choice == 'q') { 
            break; 
        } 

        if (choice == 'W' || choice == 'w') { 
            printf("Enter data for the block: "); 
            scanf(" %[^\n]", inputData); 

            // Create and allocate a new block 
            struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block)); 
            if (newBlock == NULL) {
                printf("Memory allocation failed!\n");
                return 1;
            }

            // Safely copy data into the block
            snprintf(newBlock->data, sizeof(newBlock->data), "%s", inputData);
            newBlock->next = NULL; 

            if (blockCount == 0) { 
                // This is the first block 
                firstBlock = newBlock; 
                lastBlock = newBlock; 
            } else { 
                // Link the new block to the last block 
                lastBlock->next = newBlock; 
                lastBlock = newBlock; 
            } 
            blockCount++; 
            printf("Block %d written successfully.\n", blockCount);

        } else if (choice == 'R' || choice == 'r') { 
            if (blockCount == 0) {
                printf("No blocks have been written yet.\n");
                continue;
            }

            printf("Enter the block number to read (1-%d): ", blockCount); 
            scanf("%d", &blockNumber); 

            if (blockNumber < 1 || blockNumber > blockCount) { 
                printf("Invalid block number. The valid range is 1-%d.\n", blockCount); 
            } else { 
                // Traverse the linked list to find the targeted block number
                struct Block* currentBlock = firstBlock; 
                for (int i = 1; i < blockNumber; i++) { 
                    currentBlock = currentBlock->next; 
                } 
                // Print block contents right away upon finding it
                printf("-> Block %d Data: %s\n", blockNumber, currentBlock->data); 
            } 
        } 
    } 

    // Free the allocated memory for blocks before exiting 
    struct Block* currentBlock = firstBlock; 
    while (currentBlock != NULL) { 
        struct Block* nextBlock = currentBlock->next; 
        free(currentBlock); 
        currentBlock = nextBlock; 
    } 

    printf("Memory cleared. Exiting simulation.\n");
    return 0; 
}
