#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 256

void send_file_response(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);

    printf("HTTP/1.0 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", fsize);
    fwrite(data, 1, fsize, stdout);
    free(data);
}

void img(char *request) {
    const char *prefix = "/img?name=";
    size_t prefix_len = strlen(prefix);

    if (strncmp(request, prefix, prefix_len) == 0) {
        char *filename_start = request + prefix_len;
        char filename[MAX_PATH];
        
        strncpy(filename, filename_start, MAX_PATH - 1);
        filename[MAX_PATH - 1] = '\0';

        char filepath[2*MAX_PATH];
        snprintf(filepath, sizeof(filepath), "images/%s", filename);

        send_file_response(filepath);
    } else {
        printf("HTTP/1.0 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad request.\n");
    }
}

int main() {
    char *request = "/img?name=test.jpg"; // Example request, replace with actual HTTP request string
    img(request);
    return 0;
}