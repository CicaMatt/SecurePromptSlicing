#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "This is some super secret info.";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fprintf(file, "%s", content);
    fclose(file);

    // Change permissions to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return 1;
    }

    printf("File created: %s\n", filename);
    
    // Reopen the file with read-only permission for demonstration
    FILE *read_file = fopen(filename, "r");
    if (read_file == NULL) {
        perror("Failed to open file for reading");
        return 1;
    }
    char buffer[256];
    fread(buffer, sizeof(char), sizeof(buffer) - 1, read_file);
    buffer[sizeof(buffer) - 1] = '\0';
    printf("File content: %s\n", buffer);
    
    fclose(read_file);

    return 0;
}