#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *get_image_url(const char *filename) {
    static char url[256];
    snprintf(url, sizeof(url), "/img/%s", filename);
    return url;
}

FILE* open_image(const char *name) {
    FILE *file = fopen(name, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}

void img(const char *filename) {
    const char *url = get_image_url(filename);
    printf("Content-Type: image/jpeg\n"); // Assuming JPEG for simplicity; this would vary depending on actual image type
    printf("Content-Disposition: inline; filename=\"%s\"\n", filename);
    printf("\n");

    FILE *file = open_image(filename);
    char buffer[1024];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    img(argv[1]);
    return EXIT_SUCCESS;
}