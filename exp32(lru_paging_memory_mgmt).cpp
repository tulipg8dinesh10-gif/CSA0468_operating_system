#include <stdio.h> 
#include <stdlib.h> 

#define MAX_FRAMES 3 

void printFrames(int frames[], int n) { 
    for (int i = 0; i < n; i++) { 
        if (frames[i] == -1) { 
            printf(" - "); 
        } else { 
            printf(" %d ", frames[i]); 
        } 
    } 
    printf("\n"); 
} 

int main() { 
    int frames[MAX_FRAMES]; 
    int usageHistory[MAX_FRAMES]; // Tracks how long ago a frame was used
    int pageFaults = 0; 
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; 
    int n = sizeof(referenceString) / sizeof(referenceString[0]); 

    // Initialize frames to -1 (empty) and usage history to 0
    for (int i = 0; i < MAX_FRAMES; i++) { 
        frames[i] = -1; 
        usageHistory[i] = 0; 
    } 

    printf("Reference String: "); 
    for (int i = 0; i < n; i++) { 
        printf("%d ", referenceString[i]); 
    } 
    printf("\n\nPage Replacement Order:\n"); 

    for (int i = 0; i < n; i++) { 
        int page = referenceString[i]; 
        int pageFound = 0; 

        // 1. Check if the page is already in memory (Page Hit)
        for (int j = 0; j < MAX_FRAMES; j++) { 
            if (frames[j] == page) { 
                pageFound = 1; 
                
                // Update usage history: increment others, reset current
                for (int k = 0; k < MAX_FRAMES; k++) { 
                    if (k != j) { 
                        usageHistory[k]++; 
                    } 
                } 
                usageHistory[j] = 0; // Reset counter for the hit page
                
                printf("Page %d -> (Hit)\n", page);
                break; 
            } 
        } 

        // 2. Handle Page Fault
        if (!pageFound) { 
            printf("Page %d -> ", page); 

            // Find the Least Recently Used frame (maximum age in usageHistory)
            int lruPage = 0; 
            for (int j = 1; j < MAX_FRAMES; j++) { 
                if (usageHistory[j] > usageHistory[lruPage]) { 
                    lruPage = j; 
                } 
            } 

            int replacedPage = frames[lruPage]; 
            frames[lruPage] = page; 
            
            // Age all other frames, reset the new one
            for (int k = 0; k < MAX_FRAMES; k++) {
                if (k != lruPage) {
                    usageHistory[k]++;
                }
            }
            usageHistory[lruPage] = 0; 

            if (replacedPage != -1) { 
                printf("Replace %d with %d: ", replacedPage, page); 
            } else { 
                printf("Load into an empty frame: "); 
            } 

            printFrames(frames, MAX_FRAMES); 
            pageFaults++; 
        } 
    } 

    printf("\nTotal Page Faults: %d\n", pageFaults); 
    return 0; 
}
