#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "super_secret_info.txt";
    FILE *file;
    const char *info = "Super Secret Info";

    // Create and write to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }
    
    fprintf(file, "%s", info);
    fclose(file);

    // Change permissions to read-only for owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return 1;
    }

    // Print the name of the file
    printf("%s\n", filename);

    return 0;
}