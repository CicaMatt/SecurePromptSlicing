#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

void get_img(const char *url, char *buffer, size_t buffer_size) {
    const char *prefix = "/img";
    if (strncmp(url, prefix, strlen(prefix)) == 0 && url[strlen(prefix)] == '/') {
        snprintf(buffer, buffer_size, "images/%s", url + strlen(prefix));
    } else {
        strcpy(buffer, "");
    }
}

FILE* open_image(const char *url) {
    char path[MAX_PATH];
    get_img(url, path, sizeof(path));
    if (strlen(path) > 0) {
        return fopen(path, "rb");
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    FILE *file = open_image(url);

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Example usage: print the image name
    printf("Opened file: %s\n", url + 4); // Assuming valid URL

    fclose(file);
    return EXIT_SUCCESS;
}