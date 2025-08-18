#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";

    // Create or open the file with write access, and set permissions to 0644 (rw-r--r--)
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fclose(file);

    // Change the file's permission
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return 1;
    }
    if (chmod(filename, st.st_mode | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error setting file permissions");
        return 1;
    }

    printf("File '%s' created with necessary permissions.\n", filename);
    return 0;
}