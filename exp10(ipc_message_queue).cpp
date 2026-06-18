#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define SHM_SIZE 1024

int main(void) {
    // 1. Create a named shared memory segment
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    
        NULL,                    
        PAGE_READWRITE,          
        0,                       
        SHM_SIZE,                
        "Local\\MySharedMemory"  
    );

    if (hMapFile == NULL) {
        printf("Error: Could not create shared memory (%lu).\n", GetLastError());
        return EXIT_FAILURE;
    }

    // 2. Map the memory view for the Producer to write
    char *shm_ptr = (char *)MapViewOfFile(
        hMapFile,            
        FILE_MAP_ALL_ACCESS, 
        0,
        0,
        SHM_SIZE
    );

    if (shm_ptr == NULL) {
        printf("Error: Could not map view (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return EXIT_FAILURE;
    }

    // --- PRODUCER PHASE ---
    const char *message = "Hello, message queue!";
    strncpy(shm_ptr, message, SHM_SIZE - 1);
    shm_ptr[SHM_SIZE - 1] = '\0'; // Ensure safe null-termination
    
    // Exactly matches your target output format
    printf("Producer: Data sent to message queue: %s\n", shm_ptr);


    // --- CONSUMER PHASE ---
    // Simulating the consumer reading from the exact same memory pointer
    printf("Consumer: Data received from message queue: %s\n", shm_ptr);


    // 3. Clean up resources safely
    UnmapViewOfFile(shm_ptr);
    CloseHandle(hMapFile);

    return EXIT_SUCCESS;
}
