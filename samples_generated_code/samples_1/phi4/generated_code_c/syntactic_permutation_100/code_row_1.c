#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    
    // Create and open file for writing, if it doesn't exist
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fclose(file);

    // Set the necessary permissions (owner read/write, group read, others none)
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP) != 0) {
        perror("Error setting file permissions");
        return 1;
    }

    printf("File '%s' created with necessary permissions.\n", filename);
    return 0;
}