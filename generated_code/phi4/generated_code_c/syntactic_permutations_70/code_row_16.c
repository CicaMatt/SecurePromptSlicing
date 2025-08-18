#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void save_uploaded_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", content);
    fclose(file);
}

int upload_file(const char *uploaded_filename, const char *content) {
    char target_path[256];
    snprintf(target_path, sizeof(target_path), "./uploads/%s", uploaded_filename);

    // Create uploads directory if it does not exist
    mkdir("./uploads", 0777);

    save_uploaded_file(target_path, content);
    printf("File '%s' has been saved successfully.\n", uploaded_filename);
    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is a test file content.";

    upload_file(filename, content);

    return 0;
}