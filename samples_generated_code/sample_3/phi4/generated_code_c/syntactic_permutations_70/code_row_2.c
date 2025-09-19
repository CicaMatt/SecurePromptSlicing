#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void save_uploaded_file(const char *filename, const unsigned char *file_data, size_t data_size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    
    if (fwrite(file_data, 1, data_size, file) != data_size) {
        perror("Failed to write to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void handle_file_upload(const char *filename, const unsigned char *file_data, size_t data_size) {
    // For this example, we'll save the uploaded file with a fixed name "uploaded.bin"
    save_uploaded_file("uploaded.bin", file_data, data_size);

    printf("File %s uploaded and saved successfully.\n", filename);
}

int main() {
    const char *filename = "testfile.txt";
    unsigned char buffer[BUFFER_SIZE];

    // Simulating reading a file into the buffer
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open test file for reading");
        return EXIT_FAILURE;
    }

    size_t data_size = fread(buffer, 1, BUFFER_SIZE, file);
    fclose(file);

    // Handling the file upload
    handle_file_upload(filename, buffer, data_size);

    return EXIT_SUCCESS;
}