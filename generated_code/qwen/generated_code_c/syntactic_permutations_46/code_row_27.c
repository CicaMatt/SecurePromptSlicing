#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_response(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filelen = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc((filelen+1)*sizeof(char));
    fread(buffer, filelen, 1, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nConnection: close\r\nContent-Length: %ld\r\n\r\n", filelen);
    fwrite(buffer, filelen, 1, stdout);
    free(buffer);
}

void img(const char* name) {
    char filename[1024];
    snprintf(filename, sizeof(filename), "images/%s", name);
    send_response(filename);
}

int main(int argc, char** argv) {
    if (argc != 3 || strcmp(argv[1], "/img") != 0) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nBad request.\n");
        return 1;
    }

    img(argv[2]);
    return 0;
}