#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    file = fopen("important_config", "w");
    
    if (file == NULL) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }

    // Set permissions to read and write for owner, and read for group and others
    if (fchmod(fileno(file), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error setting file permissions");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Optionally add content to the file
    fprintf(file, "Configuration settings\n");

    fclose(file);

    return EXIT_SUCCESS;
}