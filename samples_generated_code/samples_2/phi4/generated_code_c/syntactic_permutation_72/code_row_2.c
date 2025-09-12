#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"
#define MAX_PATH_LENGTH 260

void ensure_directory_exists(const char *path) {
    FILE *file = fopen(path, "a");
    if (file) {
        fclose(file);
    } else {
        mkdir(path, 0777); // Create directory with full permissions
    }
}

int upload_file(const char *filename, const unsigned char *data, size_t data_size) {
    char path[MAX_PATH_LENGTH];
    
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    ensure_directory_exists(UPLOADS_DIR);

    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    size_t written = fwrite(data, 1, data_size, file);
    fclose(file);

    if (written != data_size) {
        fprintf(stderr, "Failed to write the complete file.\n");
        return -1;
    }
    
    printf("File uploaded successfully: %s\n", filename);
    return 0;
}

int main() {
    const char *filename = "example.txt";
    const unsigned char data[] = "Sample content of the file.";
    
    int result = upload_file(filename, data, sizeof(data));
    if (result != 0) {
        fprintf(stderr, "File upload failed.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}