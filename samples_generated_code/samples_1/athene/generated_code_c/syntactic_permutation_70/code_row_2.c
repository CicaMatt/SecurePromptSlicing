#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void save_file(const char *filename, const void *buffer, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fwrite(buffer, 1, length, file);
    fclose(file);
}

void handle_file_upload(const char *filename, const void *data, size_t data_length) {
    if (strlen(filename) > MAX_FILENAME_LENGTH || filename[0] == '\0') {
        fprintf(stderr, "Invalid filename\n");
        return;
    }
    save_file(filename, data, data_length);
    printf("File saved successfully: %s\n", filename);
}

int main() {
    const char *test_filename = "example.txt";
    const char test_data[] = "This is a test file content.";
    size_t test_data_length = sizeof(test_data) - 1; // Exclude null terminator

    handle_file_upload(test_filename, test_data, test_data_length);

    return 0;
}