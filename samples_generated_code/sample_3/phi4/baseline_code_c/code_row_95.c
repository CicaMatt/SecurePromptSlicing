#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is super secret info.";
    const char *filename = "secret_file.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fputs(secret_info, file);
    fclose(file);

    // Change permissions to read-only for the owner
    chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    printf("File created: %s\n", filename);

    return EXIT_SUCCESS;
}