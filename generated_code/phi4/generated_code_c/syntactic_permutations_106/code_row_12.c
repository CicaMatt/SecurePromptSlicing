#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *file_name = "secret_info.txt";
    const char *secret_info = "This is some super secret info.";
    
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    struct stat st;
    if (stat(file_name, &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }
    
    // Change permissions to read-only for the owner
    if (chmod(file_name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("File created: %s\n", file_name);

    return EXIT_SUCCESS;
}