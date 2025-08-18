#include <stdio.h>
#include <stdlib.h>

typedef struct File {
    FILE *file;
    const char *filename;
} File;

File *open_file(const char *filename, const char *mode) {
    File *file = (File *)malloc(sizeof(File));
    if (file == NULL) return NULL;
    file->filename = filename;
    file->file = fopen(filename, mode);
    if (file->file == NULL) {
        free(file);
        return NULL;
    }
    return file;
}

void close_file(File *file) {
    if (file != NULL && file->file != NULL) {
        fclose(file->file);
    }
    free(file);
}

int main() {
    File *myFile = open_file("example.txt", "r");
    if (myFile == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Perform operations on the file here
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), myFile->file)) {
        printf("%s", buffer);
    }

    close_file(myFile);
    return EXIT_SUCCESS;
}