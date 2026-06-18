#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>
#define BUFFER_SIZE 5 
#define MAX_ITEMS 10 
int buffer[BUFFER_SIZE]; 
HANDLE sem_empty, sem_full; 
HANDLE buffer_mutex; 
int produced_items = 0, consumed_items = 0; 
DWORD WINAPI producer(LPVOID arg) { 
    while (1) { 
        WaitForSingleObject(buffer_mutex, INFINITE);
        if (produced_items >= MAX_ITEMS) {
            ReleaseMutex(buffer_mutex);
            break;
        }
        ReleaseMutex(buffer_mutex);
        WaitForSingleObject(sem_empty, INFINITE); 
        WaitForSingleObject(buffer_mutex, INFINITE); 
        for (int i = 0; i < BUFFER_SIZE; ++i) { 
            if (buffer[i] == 0) { 
                buffer[i] = produced_items + 1; 
                printf("Produced: %d\n", buffer[i]); 
                produced_items++; 
                break; 
            } 
        } 
        ReleaseMutex(buffer_mutex); 
        ReleaseSemaphore(sem_full, 1, NULL); 
        Sleep(200);
    } 
    return 0; 
} 
DWORD WINAPI consumer(LPVOID arg) { 
    while (1) { 
        WaitForSingleObject(buffer_mutex, INFINITE);
        if (consumed_items >= MAX_ITEMS) {
            ReleaseMutex(buffer_mutex);
            break;
        }
        ReleaseMutex(buffer_mutex);
        WaitForSingleObject(sem_full, INFINITE); 
        WaitForSingleObject(buffer_mutex, INFINITE); 
        for (int i = 0; i < BUFFER_SIZE; ++i) { 
            if (buffer[i] != 0) { 
                printf("Consumed: %d\n", buffer[i]); 
                buffer[i] = 0; 
                consumed_items++; 
                break; 
            } 
        } 
        ReleaseMutex(buffer_mutex); 
        ReleaseSemaphore(sem_empty, 1, NULL); 
        Sleep(400); 
    } 
    return 0; 
} 
int main(void) { 
    HANDLE producer_thread, consumer_thread; 
    sem_empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    sem_full  = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    buffer_mutex = CreateMutex(NULL, FALSE, NULL);
    if (sem_empty == NULL || sem_full == NULL || buffer_mutex == NULL) {
        printf("Error initializing synchronization objects.\n");
        return 1;
    }
    for (int i = 0; i < BUFFER_SIZE; i++) buffer[i] = 0;
    producer_thread = CreateThread(NULL, 0, producer, NULL, 0, NULL); 
    consumer_thread = CreateThread(NULL, 0, consumer, NULL, 0, NULL); 
    WaitForSingleObject(producer_thread, INFINITE); 
    WaitForSingleObject(consumer_thread, INFINITE); 
    CloseHandle(sem_empty); 
    CloseHandle(sem_full); 
    CloseHandle(buffer_mutex);
    CloseHandle(producer_thread);
    CloseHandle(consumer_thread);

    printf("\nAll items produced and consumed successfully.\n");
    return 0; 
}
