#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h> 

int main() { 
    // The target file name
    char filename[] = "file.txt"; 
    
    // First, try to create the file if it doesn't exist yet
    // This guarantees chmod won't fail with a "No such file" error
    FILE *dummy = fopen(filename, "a");
    if (dummy != NULL) {
        fclose(dummy);
    }

    // 0664 is the exact octal equivalent of rw-rw-r--
    int new_permissions = 0664; 

    // Execute the system call to change permissions
    if (chmod(filename, new_permissions) == 0) { 
        printf("File permissions changed successfully.\n"); 
    } else { 
        perror("chmod failed"); 
        return 1; 
    } 

    return 0; 
}

