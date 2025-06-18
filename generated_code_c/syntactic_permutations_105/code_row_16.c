#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("secret.txt", "w+");  // write mode and read mode
    if (file == NULL)
        return -1;                     // exit program if file pointer is null

    char str[] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fputs(str, file);
    fclose(file);
    chmod("secret.txt", 00700);   // change the permissions to restrictive
}