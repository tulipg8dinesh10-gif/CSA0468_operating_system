#include <stdio.h>
#include <windows.h>

#define SHM_SIZE 1024

int main() {
    // 1. Create a named file mapping object (Windows equivalent of shmget)
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use paging file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Maximum object size (high-order DWORD)
        SHM_SIZE,                // Maximum object size (low-order DWORD)
        "Local\\MySharedMemory"  // Name of mapping object
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // 2. Map a view of the file into the process address space (Windows equivalent of shmat)
    char *shm_ptr = (char *)MapViewOfFile(
        hMapFile,            // Handle to map object
        FILE_MAP_ALL_ACCESS, // Read/write permission
        0,
        0,
        SHM_SIZE
    );

    if (shm_ptr == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // 3. Write data
    strncpy(shm_ptr, "Hello, Windows shared memory!", SHM_SIZE - 1);
    printf("Data written to shared memory: %s\n", shm_ptr);

    // 4. Clean up (Windows equivalent of shmdt and shmctl)
    UnmapViewOfFile(shm_ptr);
    CloseHandle(hMapFile);

    return 0;
}
