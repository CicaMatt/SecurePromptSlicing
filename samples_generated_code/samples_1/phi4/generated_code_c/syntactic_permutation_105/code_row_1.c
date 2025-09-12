#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *text = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(text, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Change the permissions of the file
    if (chmod("secret.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}