#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fclose(file);

    // Set permissions to read and write for owner, read-only for group and others
    struct stat st;
    if (stat("important_config", &st) != 0) {
        perror("Error getting file status");
        return 1;
    }

    if (chmod("important_config", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error setting permissions");
        return 1;
    }
    
    printf("File created with necessary permissions.\n");
    return 0;
}