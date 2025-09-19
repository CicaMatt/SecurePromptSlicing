#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";

    // Set the mode to create the file with read and write permissions for owner, read permission for group and others.
    umask(022);

    if ((file = fopen(filename, "w")) == NULL) {
        perror("Error opening file");
        return 1;
    }

    fclose(file);

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        perror("Error getting file status");
        return 1;
    }

    // Set the permissions to read and write for owner, read-only for group and others
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error setting file permissions");
        return 1;
    }

    printf("%s created with appropriate permissions.\n", filename);
    
    return 0;
}