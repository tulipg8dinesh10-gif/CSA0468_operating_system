#include <stdio.h> 
#include <stdlib.h> 

#define MAX_BLOCKS 100

// Structure to represent a block 
struct Block { 
    int blockNumber; 
    char data[256]; // Adjust the size as needed for your blocks 
}; 

int main() { 
    FILE *file; 
    struct Block block; 
    int targetBlockNumber; 
    
    // Create an index block that contains byte offsets to data blocks 
    long indexBlock[MAX_BLOCKS]; 
    
    // Initialize index array to -1 to safely represent unallocated blocks
    for (int i = 0; i < MAX_BLOCKS; i++) {
        indexBlock[i] = -1;
    }

    // Open or create a file in binary write mode
    file = fopen("indexed_file.dat", "wb"); 
    if (file == NULL) { 
        printf("Error opening the file for writing.\n"); 
        return 1; 
    } 

    // Write blocks and update the index block 
    printf("Enter blocks (Enter '0' as block number to exit):\n"); 
    while (1) { 
        printf("Block Number (1-%d): ", MAX_BLOCKS - 1); 
        scanf("%d", &block.blockNumber); 
        
        if (block.blockNumber <= 0 || block.blockNumber >= MAX_BLOCKS) { 
            break; 
        } 

        // Input data for the block 
        printf("Data: "); 
        scanf(" %[^\n]", block.data); 

        // Map the current file position index *before* writing the block
        indexBlock[block.blockNumber] = ftell(file); 

        // Write the block to the file 
        fwrite(&block, sizeof(struct Block), 1, file); 
    } 
    
    // Close the file after exiting the input loop
    fclose(file); 

    // Reopen the file in binary read mode
    file = fopen("indexed_file.dat", "rb"); 
    if (file == NULL) { 
        printf("Error opening the file for reading.\n"); 
        return 1; 
    } 

    // Read a specific block from the file using direct indexing
    while (1) { 
        printf("\nEnter the block number to read (0 to exit): "); 
        scanf("%d", &targetBlockNumber); 
        
        if (targetBlockNumber <= 0 || targetBlockNumber >= MAX_BLOCKS) { 
            break; 
        } 

        // Check if the block has a valid recorded file offset
        if (indexBlock[targetBlockNumber] == -1) { 
            printf("Block not found / Not allocated.\n"); 
        } else { 
            // Seek directly to the data block using the pre-recorded byte offset
            fseek(file, indexBlock[targetBlockNumber], SEEK_SET); 
            
            fread(&block, sizeof(struct Block), 1, file); 
            printf("-> Block Found!\n");
            printf("   Block Number: %d\n", block.blockNumber); 
            printf("   Data: %s\n", block.data); 
        } 
    } 

    fclose(file); 
    return 0; 
}
