#include <stdio.h> 
#include <stdlib.h> 

// Structure to represent a record 
struct Record { 
    int recordNumber; 
    char data[256]; // Adjust the size as needed for your records 
}; 

int main() { 
    FILE *file; 
    struct Record record; 
    int searchRecordNumber; 

    // Open or create a file in binary write mode
    file = fopen("sequential_file.dat", "wb"); 
    if (file == NULL) { 
        printf("Error opening the file for writing.\n"); 
        return 1; 
    } 

    // Write records sequentially to the file 
    printf("Enter records (Enter '0' as record number to exit):\n"); 
    while (1) { 
        printf("Record Number: "); 
        scanf("%d", &record.recordNumber); 
        
        if (record.recordNumber == 0) { 
            break; 
        } 

        // Input data for the record (reads strings with spaces safely)
        printf("Data: "); 
        scanf(" %[^\n]", record.data); 

        // Write the record to the file 
        fwrite(&record, sizeof(struct Record), 1, file); 
    } 
    fclose(file); 

    // Reopen the file in binary read mode
    file = fopen("sequential_file.dat", "rb"); 
    if (file == NULL) { 
        printf("Error opening the file for reading.\n"); 
        return 1; 
    } 

    // Read a specific record from the file sequentially
    while (1) { 
        printf("\nEnter the record number to read (0 to exit): "); 
        scanf("%d", &searchRecordNumber); 
        
        if (searchRecordNumber == 0) { 
            break; 
        } 

        int recordFound = 0;
        rewind(file); // Reset the file pointer to the beginning before every search

        // Read and display records up to the requested record 
        while (fread(&record, sizeof(struct Record), 1, file)) { 
            if (record.recordNumber == searchRecordNumber) { 
                printf("-> Record Found!\n");
                printf("   Record Number: %d\n", record.recordNumber); 
                printf("   Data: %s\n", record.data); 
                recordFound = 1;
                break; // Found it, stop scanning this time
            } 
        } 

        if (!recordFound) {
            printf("Record %d not found in the file.\n", searchRecordNumber);
        }
    } 

    fclose(file); 
    return 0; 
}
