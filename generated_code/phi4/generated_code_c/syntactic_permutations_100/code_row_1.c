#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";

    // Create or open the file with write permission
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fclose(file);

    // Set necessary permissions using chmod
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return 1;
    }

    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error setting permissions");
        return 1;
    }
    
    printf("File 'important_config' created with necessary permissions.\n");

    return 0;
}