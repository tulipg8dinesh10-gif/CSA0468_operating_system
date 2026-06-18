#include <stdio.h> 
#include <stdlib.h>

struct Employee { 
    int empId; 
    char empName[50]; 
    float empSalary;
}; 

int main() { 
    FILE *filePtr; 
    struct Employee emp; 
    
    // Attempt to open for reading and writing
    filePtr = fopen("employee.dat", "rb+"); 
    if (filePtr == NULL) { 
        // If file doesn't exist, create it with wb+
        filePtr = fopen("employee.dat", "wb+"); 
        if (filePtr == NULL) { 
            printf("Error creating the file.\n"); 
            return 1; 
        } 
    } // FIXED: Added missing closing brace for the outer filePtr check

    int choice; 
    
    do { // FIXED: Removed the empty braces that were closing the loop prematurely
        printf("\n--- Employee Database Menu ---\n"); 
        printf("1. Add Employee\n"); 
        printf("2. Display Employee Details\n"); 
        printf("3. Update Employee Details\n"); 
        printf("4. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 

        switch (choice) { 
            case 1: 
                printf("Enter Employee ID: "); 
                scanf("%d", &emp.empId); 
                printf("Enter Employee Name: "); 
                scanf("%s", emp.empName); 
                printf("Enter Employee Salary: "); 
                scanf("%f", &emp.empSalary); 
                
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET); 
                fwrite(&emp, sizeof(struct Employee), 1, filePtr); 
                printf("Employee details added successfully.\n"); 
                break; 
                
            case 2: 
                printf("Enter Employee ID to display: "); 
                scanf("%d", &emp.empId); 
                
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET); 
                // Check if we can successfully read a valid record
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1 && emp.empId != 0) {
                    printf("\nEmployee ID: %d\n", emp.empId); 
                    printf("Employee Name: %s\n", emp.empName); 
                    printf("Employee Salary: %.2f\n", emp.empSalary); 
                } else {
                    printf("Record not found for ID %d.\n", emp.empId);
                }
                break; 
                
            case 3: 
                printf("Enter Employee ID to update: "); 
                scanf("%d", &emp.empId); 
                
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET); 
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1 && emp.empId != 0) {
                    printf("Current Name: %s, Current Salary: %.2f\n", emp.empName, emp.empSalary);
                    printf("Enter New Employee Name: "); 
                    scanf("%s", emp.empName); 
                    printf("Enter New Employee Salary: "); 
                    scanf("%f", &emp.empSalary); 
                    
                    fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET); 
                    fwrite(&emp, sizeof(struct Employee), 1, filePtr); 
                    printf("Employee details updated successfully.\n"); 
                } else {
                    printf("Record does not exist to update.\n");
                }
                break; 
                
            case 4: 
                printf("Exiting database application.\n");
                break; 
                
            default: 
                printf("Invalid choice. Please try again.\n"); 
        } 
    } while (choice != 4); 

    fclose(filePtr); 
    return 0;
}
