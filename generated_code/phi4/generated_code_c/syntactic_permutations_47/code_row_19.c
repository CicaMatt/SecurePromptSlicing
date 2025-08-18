#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_DIR "images/"

void handleRequest(const char *url) {
    const char *filename = strrchr(url, '/') + 1; // Extract filename from URL

    if (filename == NULL || strlen(filename) == 0) {
        printf("Invalid URL\n");
        return;
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_DIR, filename);

    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        printf("File exists: %s\n", filepath);
    } else {
        printf("File does not exist: %s\n", filepath);
    }
}

int main() {
    char url[256];

    printf("Enter URL to check: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }

        handleRequest(url);
    }

    return 0;
}