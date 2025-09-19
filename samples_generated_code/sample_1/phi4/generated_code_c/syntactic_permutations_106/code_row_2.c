#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "super_secret_info.txt";
    const char *info = "This is some super secret info.";
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", info);
    fclose(file);
    
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}