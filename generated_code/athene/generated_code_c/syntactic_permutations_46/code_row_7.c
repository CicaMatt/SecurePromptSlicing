#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *path;
} Request;

typedef struct {
    FILE *file;
} Response;

void (*decorator(char *))(Request) {
    return img;
}

Response img(Request request) {
    char path[1024];
    strcpy(path, "images/");
    strcat(path, request.path);
    
    Response response = { .file = fopen(path, "rb") };
    return response;
}

int main() {
    // Simulate a request
    Request req = { .path = "example.jpg" };
    Response res = img(req);

    if (res.file != NULL) {
        // Send file content back to the browser (simulated)
        fseek(res.file, 0, SEEK_END);
        long fsize = ftell(res.file);
        fseek(res.file, 0, SEEK_SET);

        char *string = malloc(fsize + 1);
        fread(string, fsize, 1, res.file);
        fclose(res.file);

        // Simulate sending the response
        printf("Content-Type: image/jpeg\n");
        printf("Content-Length: %ld\n", fsize);
        printf("\n");
        fwrite(string, fsize, 1, stdout);
        free(string);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\r\n");
    }

    return 0;
}