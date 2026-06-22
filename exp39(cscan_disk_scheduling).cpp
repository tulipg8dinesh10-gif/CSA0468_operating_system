#include <stdio.h> 
#include <stdlib.h> 

#define DISK_SIZE 199 // Standard max cylinder limit for textbook problems

int main() { 
    int n, head, seek_time = 0; 

    printf("Enter the number of disk requests: "); 
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    int request_queue[n]; 
    printf("Enter the disk request queue:\n"); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &request_queue[i]); 
    } 

    printf("Enter the initial position of the disk head: "); 
    scanf("%d", &head); 

    // Sort the request queue in ascending order (Bubble Sort)
    for (int i = 0; i < n - 1; i++) { 
        for (int j = i + 1; j < n; j++) { 
            if (request_queue[i] > request_queue[j]) { 
                int temp = request_queue[i]; 
                request_queue[i] = request_queue[j]; 
                request_queue[j] = temp; 
            } 
        } 
    } 

    // Find the point where the head is positioned relative to sorted requests
    int index = 0;
    while (index < n && request_queue[index] < head) {
        index++;
    }

    printf("\nC-SCAN Disk Scheduling:\n"); 
    printf("Head Movement Sequence: %d", head);

    // Phase 1: Service requests to the right of the initial head position
    for (int i = index; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    // If there are still unserviced requests left on the left side
    if (index > 0) {
        // Move to the upper boundary edge of the disk
        seek_time += abs(head - DISK_SIZE);
        head = DISK_SIZE;
        printf(" -> %d", head);

        // Circular jump: Move completely back to the lower boundary edge (0)
        seek_time += abs(head - 0);
        head = 0;
        printf(" -> %d", head);

        // Phase 2: Service the remaining requests starting from the beginning (0)
        for (int i = 0; i < index; i++) {
            seek_time += abs(head - request_queue[i]);
            head = request_queue[i];
            printf(" -> %d", head);
        }
    }

    printf("\n\nTotal Seek Time: %d\n", seek_time); 
    printf("Average Seek Time: %.2f\n", (float)seek_time / n); 

    return 0; 
}
