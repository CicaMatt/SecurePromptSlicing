#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename) {
    const char *uploads_dir = "uploads";
    char filepath[256];
    
    create_directory(uploads_dir);

    snprintf(filepath, sizeof(filepath), "%s/%s", uploads_dir, filename);

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return -1;
    }

    // Simulate saving the content to a file
    const char *content = "This is the content of the uploaded file.";
    if (fwrite(content, strlen(content), 1, file) != 1) {
        perror("Error writing to file");
        fclose(file);
        return -1;
    }

    fclose(file);

    printf("File '%s' saved successfully in the 'uploads' directory.\n", filename);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    if (upload_file(filename) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}