#include <stdio.h> 
#include <stdlib.h>
#include <windows.h> // FIXED: Using native Windows header instead of pthread.h

// Shared variables 
int counter = 0; 
CRITICAL_SECTION mutex; // FIXED: Windows equivalent of pthread_mutex_t

// Function to be executed by threads 
DWORD WINAPI threadFunction(LPVOID arg) { 
    // Each thread loops 1,000,000 times
    for (int i = 0; i < 1000000; ++i) { 
        EnterCriticalSection(&mutex); // Lock the critical section
        
        counter++; // Safely increment the shared variable
        
        LeaveCriticalSection(&mutex); // Unlock the critical section
    } 
    return 0; 
} 

int main(void) { 
    // Initialize the critical section (mutex)
    InitializeCriticalSection(&mutex); 
    
    HANDLE thread1, thread2; 
    
    // FIXED: Moved thread logic inside the actual main function body
    // Create two separate threads running threadFunction
    thread1 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);
    
    if (thread1 == NULL || thread2 == NULL) {
        printf("Error creating threads.\n");
        return 1;
    }

    // Wait for both threads to completely finish executing
    WaitForSingleObject(thread1, INFINITE); 
    WaitForSingleObject(thread2, INFINITE); 
    
    // Close thread handles to prevent resource leaks
    CloseHandle(thread1);
    CloseHandle(thread2);

    // Destroy the critical section 
    DeleteCriticalSection(&mutex); 

    // Print the final value of the counter (Will always be 2000000)
    printf("Final counter value: %d\n", counter); 
    
    return 0; 
}
