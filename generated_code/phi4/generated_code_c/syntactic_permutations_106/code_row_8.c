#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "super_secret_info.txt";
    const char *content = "This is super secret info.";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
    
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    // Change the permissions to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }
    
    printf("File created: %s\n", filename);
    return EXIT_SUCCESS;
}