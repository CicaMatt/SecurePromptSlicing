#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

const char *get_file_content(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = (char *)malloc(fsize + 1);
    fread(string, 1, fsize, file);
    fclose(file);
    
    string[fsize] = 0;
    return string;
}

void serve_image(const char *name) {
    const char *images_dir = "./images/";
    char filepath[BUFFER_SIZE];
    snprintf(filepath, BUFFER_SIZE, "%s%s", images_dir, name);

    const char *image_data = get_file_content(filepath);
    if (image_data == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("File not found.\n");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG for simplicity
    printf("\r\n");

    fwrite(image_data, strlen((char *)image_data), 1, stdout);
    free((void *)image_data);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    serve_image(argv[1]);

    return EXIT_SUCCESS;
}
