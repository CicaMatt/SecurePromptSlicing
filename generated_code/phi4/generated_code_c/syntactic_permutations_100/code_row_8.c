#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt";
    int permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // Read and write for owner, read for group and others

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fclose(file);

    if (chmod(filename, permission) != 0) {
        perror("Error setting permissions");
        return EXIT_FAILURE;
    }

    printf("File created and permissions set successfully.\n");

    return EXIT_SUCCESS;
}