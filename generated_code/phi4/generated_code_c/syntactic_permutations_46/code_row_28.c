#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

void send_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.0 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\n\r\n", size);

    char buffer[1024];
    while (size > 0) {
        int bytes = fread(buffer, 1, sizeof(buffer), file);
        fwrite(buffer, 1, bytes, stdout);
        size -= bytes;
    }

    fclose(file);
}

void img_function(const char *url) {
    char filename[MAX_PATH];

    // Extracting the name parameter from the URL
    const char *param_start = strstr(url, "name=");
    if (param_start == NULL) {
        printf("HTTP/1.0 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing 'name' parameter.");
        return;
    }
    
    param_start += strlen("name=");

    // Copying the filename up to a space or end of string
    size_t len = strcspn(param_start, " ");
    if (len >= MAX_PATH - 1) {
        printf("HTTP/1.0 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nFilename too long.");
        return;
    }

    strncpy(filename, param_start, len);
    filename[len] = '\0';

    // Constructing the full file path
    snprintf(filename + strlen(filename), sizeof(filename) - strlen(filename), "/images/%s", filename);

    send_file(filename);
}

int main() {
    const char *url = "http://example.com/img?name=sample.jpg";
    img_function(url);
    return 0;
}