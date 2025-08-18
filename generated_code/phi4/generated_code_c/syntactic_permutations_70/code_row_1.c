#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define BUFFER_SIZE 4096

int save_uploaded_file(const char *filename, const char *data, size_t data_size) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return -1;
    }

    size_t written = fwrite(data, 1, data_size, file);
    fclose(file);

    if (written != data_size) {
        fprintf(stderr, "Error: Only %zu bytes were written out of %zu\n", written, data_size);
        return -1;
    }

    return 0;
}

int upload_file(const char *filename, const char *filedata) {
    // Ensure the uploads directory exists
    mkdir(UPLOADS_DIR, 0777);

    return save_uploaded_file(filename, filedata, strlen(filedata));
}

int main() {
    // Simulate a file upload
    const char *filename = "uploaded_example.txt";
    const char *filedata = "This is some example content of the uploaded file.";

    if (upload_file(filename, filedata) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}