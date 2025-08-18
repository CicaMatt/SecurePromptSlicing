#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *)malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);

    data[fsize] = 0;
    printf("Content-Length: %ld\r\n", fsize);
    printf("Content-Type: image/jpeg\r\n");
    printf("\r\n");

    fwrite(data, 1, fsize, stdout);
    free(data);
}

void img(const char *name) {
    char filename[256];
    snprintf(filename, sizeof(filename), "images/%s", name);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
    } else {
        send_file(file);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}