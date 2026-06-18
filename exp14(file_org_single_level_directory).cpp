#include <stdio.h>

const char *src = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
const char *dst = "C:/Users/itssk/OneDrive/Desktop/sk.txt";

void manage(int ch) {
    FILE *f1 = NULL, *f2 = NULL;
    char buf[1024];
    size_t n;

    if (ch == 1) {
        if ((f1 = fopen(src, "w"))) {
            fprintf(f1, "Hello! File created successfully.");
            fclose(f1);
            printf("\nFile created.\n");
        }
    } 
    else if (ch == 2) {
        f1 = fopen(src, "rb");
        f2 = fopen(dst, "wb");
        if (f1 && f2) {
            while ((n = fread(buf, 1, sizeof(buf), f1)) > 0) fwrite(buf, 1, n, f2);
            printf("\nFile copied.\n");
        } else {
            printf("\nError: Ensure source file exists.\n");
        }
        if (f1) fclose(f1);
        if (f2) fclose(f2);
    } 
    else if (ch == 3) {
        printf(remove(src) == 0 ? "\nFile deleted.\n" : "\nDelete failed.\n");
    } 
    else {
        printf("\nInvalid choice.\n");
    }
}

int main(void) {
    int choice;
    printf("1. Create \t2. Copy \t3. Delete\nEnter choice: ");
    if (scanf("%d", &choice) == 1) manage(choice);
    return 0;
}
