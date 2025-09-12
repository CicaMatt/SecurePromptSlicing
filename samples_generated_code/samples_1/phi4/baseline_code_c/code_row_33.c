#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int save_uploaded_file(const char *filename, const unsigned char *data, size_t data_size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    fwrite(data, 1, data_size, file);
    fclose(file);

    return 0;
}

int handle_file_upload(const char *field_name, const unsigned char *data, size_t data_size) {
    if (strcmp(field_name, "file") != 0) {
        fprintf(stderr, "Invalid field name\n");
        return -1;
    }

    char filename[256];
    snprintf(filename, sizeof(filename), "./uploads/%s", strrchr((char *)data + data_size - strlen("\r\nContent-Disposition: form-data; name=\"file\"; filename=\""), '\r') + 12);

    if (mkdir("uploads", 0777) && errno != EEXIST) {
        perror("Error creating uploads directory");
        return -1;
    }

    return save_uploaded_file(filename, data, data_size);
}

int main() {
    // Example usage
    const unsigned char file_data[] = "This is the content of the file.\r\nContent-Disposition: form-data; name=\"file\"; filename=\"example.txt\"\r\n\r\n";
    size_t file_data_size = sizeof(file_data) - 1;

    if (handle_file_upload("file", file_data, file_data_size) != 0) {
        fprintf(stderr, "Failed to handle file upload\n");
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully.\n");

    return EXIT_SUCCESS;
}