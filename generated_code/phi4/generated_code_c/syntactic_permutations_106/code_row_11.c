#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret_file.txt";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fputs(secret_info, file);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    // Change permissions to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }
    
    printf("File created: %s\n", filename);
    return 0;
}