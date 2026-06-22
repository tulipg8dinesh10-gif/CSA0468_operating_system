#include <stdio.h> 
#define MAX_MEMORY 1000 
int memory[MAX_MEMORY]; 
void initializeMemory() { 
    for (int i = 0; i < MAX_MEMORY; i++) { 
        memory[i] = -1;
    } 
} 
void displayMemory() { 
    int i, j; 
    int count = 0; 
    printf("\n--- Memory Status ---\n"); 
    for (i = 0; i < MAX_MEMORY; i++) { 
        if (memory[i] == -1) { 
            count++; 
            j = i; 
            while (j < MAX_MEMORY && memory[j] == -1) { 
                j++; 
            } 
            printf("Free memory block %d-%d (Size: %d)\n", i, j - 1, j - i); 
            i = j - 1; 
        } 
    } 
    if (count == 0) { 
        printf("No free memory available.\n"); 
    } 
    printf("---------------------\n");
} 
void allocateMemory(int processId, int size) { 
    int start = -1; 
    int blockSize = 0; 
    
    for (int i = 0; i < MAX_MEMORY; i++) { 
        if (memory[i] == -1) { 
            if (blockSize == 0) { 
                start = i; 
            } 
            blockSize++; 
        } else { 
            blockSize = 0; // Reset counter if an allocated block is hit
        } 
        if (blockSize >= size) { 
            break; // First fit found, stop searching
        } 
    } 
    if (blockSize >= size) { 
        for (int i = start; i < start + size; i++) { 
            memory[i] = processId; 
        } 
        printf("Allocated memory block %d-%d to Process %d\n", start, start + size - 1, processId); 
    } else { 
        printf("Memory allocation for Process %d failed (not enough contiguous memory of size %d).\n", processId, size); 
    } 
} 
void deallocateMemory(int processId) { 
    int found = 0;
    for (int i = 0; i < MAX_MEMORY; i++) { 
        if (memory[i] == processId) { 
            memory[i] = -1; 
            found = 1;
        } 
    } 
    if (found) {
        printf("Memory released by Process %d\n", processId); 
    } else {
        printf("Process %d not found in memory.\n", processId);
    }
} 
int main() { 
    initializeMemory(); 
    displayMemory(); 
    allocateMemory(1, 200); 
    displayMemory(); 
    allocateMemory(2, 300); 
    displayMemory(); 
    deallocateMemory(1); 
    displayMemory(); 
    allocateMemory(3, 400); 
    displayMemory(); 
    return 0; 
}
