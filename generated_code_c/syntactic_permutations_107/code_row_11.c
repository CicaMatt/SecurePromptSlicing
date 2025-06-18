// Import necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Change file permissions to restrictive 
    chmod("secret.txt", 0744);

    // Write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to secret.txt
    FILE *file = fopen("secret.txt", "w");
    char *str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fputs(str, file);
    fclose(file);

    // Print . to the standard output (stdout)
    printf(".");

    return 0;
}