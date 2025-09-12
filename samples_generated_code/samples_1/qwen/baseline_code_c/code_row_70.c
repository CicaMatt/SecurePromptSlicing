#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"

int save_pdf_file(const char *filename, const unsigned char *data, size_t data_size) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(full_path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    size_t written = fwrite(data, 1, data_size, file);
    fclose(file);

    if (written != data_size) {
        perror("Failed to write all data to file");
        remove(full_path); // Clean up partial file
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filename> <base64_encoded_pdf_data>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *encoded_data = argv[2];

    // Decode base64 encoded data
    unsigned int data_size;
    unsigned char *data = (unsigned char *)malloc(strlen(encoded_data));
    if (!data) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Placeholder for actual base64 decoding logic
    // For demonstration, we assume the input is already decoded binary data
    memcpy(data, encoded_data, strlen(encoded_data));
    data_size = strlen(encoded_data);

    int result = save_pdf_file(filename, data, data_size);
    free(data);

    if (result == 0) {
        printf("File saved successfully.\n");
    } else {
        fprintf(stderr, "Failed to save file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}