#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void handle_http_request(const char *request, const char *upload_path) {
    char response[1024];
    char boundary[256];
    sscanf(request, "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=%s", boundary);

    FILE *fp = fopen(upload_path, "wb");
    if (!fp) {
        sprintf(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n");
        printf("%s", response);
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, stdin)) > 0) {
        if (strstr(buffer, boundary)) {
            break; // End of the file data
        }
        fwrite(buffer, 1, bytes_read, fp);
    }

    fclose(fp);

    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nFile uploaded");
    printf("%s", response);
}

int main() {
    const char *upload_path = "./uploads/";
    mkdir(upload_path, 0777); // Ensure the upload directory exists

    char request[BUFFER_SIZE] = {0};
    int bytes_read;

    while ((bytes_read = fread(request, 1, BUFFER_SIZE - 1, stdin)) > 0) {
        if (strncmp(request, "POST /", 6) == 0) {
            handle_http_request(request, upload_path);
            break;
        }
    }

    return 0;
}