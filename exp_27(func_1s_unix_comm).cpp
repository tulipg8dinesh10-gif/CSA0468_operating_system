#include <stdio.h>
#include <string.h>

int main()
{
    char fn[50], pat[50], temp[200];
    FILE *fp;

    printf("Enter file name : ");
    scanf("%s", fn);

    printf("Enter the pattern : ");
    scanf("%s", pat);

    fp = fopen(fn, "r");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    while (fgets(temp, sizeof(temp), fp) != NULL)
    {
        if (strstr(temp, pat) != NULL)
        {
            printf("%s", temp);
        }
    }

    fclose(fp);
    return 0;
}
