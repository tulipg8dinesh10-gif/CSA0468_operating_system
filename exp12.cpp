#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

#define NUM_PHILOSOPHERS 5 

CRITICAL_SECTION chopsticks[NUM_PHILOSOPHERS]; 

DWORD WINAPI philosopherLifeCycle(LPVOID arg) { 
    int id = *((int*)arg); 
    free(arg); 
    
    int left_chopstick = id; 
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS; 
    
    while (1) { 
        printf("Philosopher %d is thinking...\n", id); 
        Sleep(rand() % 1500 + 500); 
        
        // Locking Phase
        if (id % 2 != 0) {
            EnterCriticalSection(&chopsticks[right_chopstick]);
            EnterCriticalSection(&chopsticks[left_chopstick]);
        } else {
            EnterCriticalSection(&chopsticks[left_chopstick]);
            EnterCriticalSection(&chopsticks[right_chopstick]);
        }
        
        printf("Philosopher %d is eating...\n", id); 
        Sleep(rand() % 1500 + 500); 
        
        // Unlocking Phase
        if (id % 2 != 0) {
            LeaveCriticalSection(&chopsticks[left_chopstick]);
            LeaveCriticalSection(&chopsticks[right_chopstick]); 
        } else {
            LeaveCriticalSection(&chopsticks[right_chopstick]);
            LeaveCriticalSection(&chopsticks[left_chopstick]);
        }
    } 
    return 0;
} 

int main(void) { 
    HANDLE philosophers[NUM_PHILOSOPHERS];    
    srand((unsigned int)sizeof(NULL));
    
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) { 
        InitializeCriticalSection(&chopsticks[i]); 
    } 
    
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) { 
        // FIXED: Added (int*) typecast to satisfy stricter C++ compilers
        int* philosopher_id = (int*)malloc(sizeof(int));
        if (philosopher_id == NULL) {
            perror("Allocation failed");
            return EXIT_FAILURE;
        }
        *philosopher_id = i; 
        
        philosophers[i] = CreateThread(
            NULL, 
            0, 
            philosopherLifeCycle, 
            philosopher_id, 
            0, 
            NULL
        ); 
    } 
    
    WaitForMultipleObjects(NUM_PHILOSOPHERS, philosophers, TRUE, INFINITE); 
    
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) { 
        DeleteCriticalSection(&chopsticks[i]); 
        CloseHandle(philosophers[i]);
    } 
    
    return 0; 
}
