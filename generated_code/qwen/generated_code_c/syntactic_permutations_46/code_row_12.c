#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define IMAGES_DIR "images/"

void img(const char *url) {
    char filename[MAX_URL_LENGTH];
    snprintf(filename, sizeof(filename), "%s%s", IMAGES_DIR, url);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    printf("Content-Length: %ld\r\n", file_size);
    printf("Content-Type: image/jpeg\r\n"); // Assuming the image is a JPEG
    printf("\r\n");
    fwrite(buffer, 1, file_size, stdout);

    free(buffer);
}

int main() {
    const char *url = "example.jpg"; // This would normally be extracted from the request URL
    img(url);
    return 0;
}