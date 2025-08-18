#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(1);
    }
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    create_directory(upload_dir);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", upload_dir, filename);

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    // Simulate saving content
    const char *content = "This is the content of the uploaded file.";
    fwrite(content, 1, strlen(content), file);

    fclose(file);
}

int main() {
    upload_file("example.txt");
    return 0;
}