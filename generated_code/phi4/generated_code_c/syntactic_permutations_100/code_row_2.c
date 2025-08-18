#include <stdio.h>
#include <sys/stat.h>

int main() {
    // Define the filename
    const char *filename = "important_config";

    // Create and open the file in write mode, truncating it if it exists
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Close the file after creation to apply permissions
    fclose(file);

    // Define the necessary permissions: rw-r--r--
    mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // Change the file permissions using chmod
    if (chmod(filename, permissions) != 0) {
        perror("Error changing file permissions");
        return 1;
    }

    printf("File '%s' created with necessary permissions.\n", filename);
    return 0;
}