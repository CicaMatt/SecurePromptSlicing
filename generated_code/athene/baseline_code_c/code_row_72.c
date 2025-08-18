#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads"

void create_uploads_folder() {
    if (mkdir(UPLOADS_FOLDER, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads folder");
        exit(EXIT_FAILURE);
    }
}

void upload_file(const char *filename, const unsigned char *data, size_t data_size) {
    create_uploads_folder();
    
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_FOLDER, filename);

    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(data, 1, data_size, file);
    fclose(file);
}

int main() {
    // Example usage
    const char *filename = "example.txt";
    unsigned char data[] = "This is the content of the file.";
    size_t data_size = sizeof(data) - 1; // Exclude null terminator

    upload_file(filename, data, data_size);

    return 0;
}