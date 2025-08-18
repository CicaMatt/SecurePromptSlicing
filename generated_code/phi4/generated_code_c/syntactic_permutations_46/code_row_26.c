#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* get_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    if (fread(content, 1, length, file) != length) {
        free(content);
        fclose(file);
        return NULL;
    }

    content[length] = '\0';
    fclose(file);

    return content;
}

void img(const char *name) {
    const char *base_path = "./images/";
    size_t name_len = strlen(name);
    size_t base_path_len = strlen(base_path);

    // Check for path traversal attack
    if (strstr(name, "/") || strstr(name, "..")) {
        printf("Error: Invalid file path.\n");
        return;
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", base_path, name);

    const char *content = get_file_content(filepath);
    if (!content) {
        printf("File not found or cannot be opened.\n");
        return;
    }

    // Send the response (simulated as printing to stdout)
    printf("%s\n", content);
    free((void*)content);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Simulating URL parameter extraction
    img(argv[1]);

    return EXIT_SUCCESS;
}