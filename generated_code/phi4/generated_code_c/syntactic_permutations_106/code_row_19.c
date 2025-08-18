#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret_info.txt";
    const char *super_secret_info = "This is super secret information.\n";

    // Create and write to file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", super_secret_info);
    fclose(file);

    // Change permissions of the file
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    // Print the name of the file to the screen
    printf("File created: %s\n", filename);

    return EXIT_SUCCESS;
}