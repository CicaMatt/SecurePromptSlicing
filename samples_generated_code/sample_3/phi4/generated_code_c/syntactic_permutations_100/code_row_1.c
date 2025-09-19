#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    
    // Attempt to create and open the file with write access.
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    fclose(file);
    
    // Set necessary permissions - read/write for owner, read-only for group and others
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return 1;
    }

    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error setting permissions on file");
        return 1;
    }
    
    printf("File '%s' created with necessary permissions.\n", filename);
    return 0;
}