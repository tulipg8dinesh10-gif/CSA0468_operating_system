#include <stdio.h>

#define MAX 20

int main() {
    int fragments[MAX], block_sizes[MAX], file_sizes[MAX];
    int number_of_blocks, number_of_files;
    int block_allocation[MAX];
    static int block_occupied[MAX];

    printf("Memory Management Scheme - Worst Fit\n");
    
    // 1. Inputs
    printf("Enter the number of blocks:");
    scanf("%d", &number_of_blocks);
    printf("Enter the number of files:");
    scanf("%d", &number_of_files);

    printf("\nEnter the size of the blocks:-\n");
    for (int i = 1; i <= number_of_blocks; i++) {
        printf("Block %d:", i);
        scanf("%d", &block_sizes[i]);
    }

    printf("Enter the size of the files :-\n");
    for (int i = 1; i <= number_of_files; i++) {
        printf("File %d:", i);
        scanf("%d", &file_sizes[i]);
    }

    // 2. Worst Fit Allocation Logic
    for (int i = 1; i <= number_of_files; i++) {
        int worst_index = -1;
        for (int j = 1; j <= number_of_blocks; j++) {
            if (block_occupied[j] != 1) { 
                int temp = block_sizes[j] - file_sizes[i];
                if (temp >= 0) {
                    if (worst_index == -1 || block_sizes[j] > block_sizes[worst_index]) {
                        worst_index = j;
                    }
                }
            }
        }

        if (worst_index != -1) {
            block_allocation[i] = worst_index;
            fragments[i] = block_sizes[worst_index] - file_sizes[i];
            block_occupied[worst_index] = 1;
        } else {
            block_allocation[i] = 0; 
            fragments[i] = 0;
        }
    }

    // 3. Tabular Output
    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragement\n");
    for (int i = 1; i <= number_of_files; i++) {
        if (block_allocation[i] != 0) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                   i, file_sizes[i], block_allocation[i], block_sizes[block_allocation[i]], fragments[i]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i, file_sizes[i]);
        }
    }

    return 0;
}
