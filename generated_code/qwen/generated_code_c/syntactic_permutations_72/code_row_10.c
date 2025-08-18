#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

void upload_file(const char* filename) {
    FILE *source, *destination;
    char source_path[MAX_FILENAME_LENGTH];
    char destination_path[MAX_FILENAME_LENGTH];

    snprintf(source_path, sizeof(source_path), "%s", filename);
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_DIR, filename);

    source = fopen(source_path, "rb");
    if (!source) {
        perror("Failed to open the file for reading");
        return;
    }

    destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Failed to open the file for writing");
        fclose(source);
        return;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);
}

int main() {
    upload_file("example.txt");
    return 0;
}