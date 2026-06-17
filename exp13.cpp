#include <stdio.h>
#include <stdlib.h>

void firstfit(int mp_orig[], int p[], int n, int m) {
    int mp[20];
    // Copy original partition sizes so we don't overwrite them for subsequent runs
    for(int i = 0; i < n; i++) mp[i] = mp_orig[i];

    printf("\n--- First Fit Allocation ---");
    for(int i = 0; i < m; i++) {
        int allocated = 0;
        for(int j = 0; j < n; j++) {
            if(mp[j] >= p[i]) {
                printf("\nProcess %d (%d) fits in Partition %d (%d)", i + 1, p[i], j + 1, mp[j]);
                mp[j] -= p[i];
                allocated = 1;
                break; // Move to the next process immediately
            }
        }
        if(!allocated) {
            printf("\nProcess %d (%d) must wait!", i + 1, p[i]);
        }
    }
    printf("\n");
}

void bestfit(int mp_orig[], int p[], int n, int m) {
    int mp[20];
    for(int i = 0; i < n; i++) mp[i] = mp_orig[i];

    printf("\n--- Best Fit Allocation ---");
    for(int i = 0; i < m; i++) {
        int best_idx = -1;
        for(int j = 0; j < n; j++) {
            if(mp[j] >= p[i]) {
                if(best_idx == -1 || mp[j] < mp[best_idx]) {
                    best_idx = j;
                }
            }
        }
        if(best_idx != -1) {
            printf("\nProcess %d (%d) fits in Partition %d (%d)", i + 1, p[i], best_idx + 1, mp[best_idx]);
            mp[best_idx] -= p[i];
        } else {
            printf("\nProcess %d (%d) must wait!", i + 1, p[i]);
        }
    }
    printf("\n");
}

void worstfit(int mp_orig[], int p[], int n, int m) {
    int mp[20];
    for(int i = 0; i < n; i++) mp[i] = mp_orig[i];

    printf("\n--- Worst Fit Allocation ---");
    for(int i = 0; i < m; i++) {
        int worst_idx = -1;
        for(int j = 0; j < n; j++) {
            if(mp[j] >= p[i]) {
                if(worst_idx == -1 || mp[j] > mp[worst_idx]) {
                    worst_idx = j;
                }
            }
        }
        if(worst_idx != -1) {
            printf("\nProcess %d (%d) fits in Partition %d (%d)", i + 1, p[i], worst_idx + 1, mp[worst_idx]);
            mp[worst_idx] -= p[i];
        } else {
            printf("\nProcess %d (%d) must wait!", i + 1, p[i]);
        }
    }
    printf("\n");
}

int main(void) {
    int m, n, mp[20], p[20], ch;

    printf("Number of memory partitions : ");
    scanf("%d", &n);
    printf("Number of processes : ");
    scanf("%d", &m);

    printf("Enter the memory partitions :\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &mp[i]);
    }

    printf("Enter process sizes :\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice : ");
    scanf("%d", &ch);

    switch(ch) {
        case 1:
            firstfit(mp, p, n, m);
            break;
        case 2:
            bestfit(mp, p, n, m);
            break;
        case 3:
            worstfit(mp, p, n, m);
            break;
        default:
            printf("\nInvalid Choice!\n");
            break;
    }

    return 0;
}
