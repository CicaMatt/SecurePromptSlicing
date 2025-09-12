#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    const char *name;
} Request;

typedef struct {
    FILE *file;
} Response;

void send_response(Response res) {
    if (res.file != NULL) {
        char buffer[BUFFER_SIZE];
        while (!feof(res.file)) {
            size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, res.file);
            if (bytesRead > 0) {
                fwrite(buffer, 1, bytesRead, stdout); // Simulate sending data to the browser
            }
        }
        fclose(res.file);
    } else {
        fprintf(stderr, "File not found\n");
    }
}

Response img(Request req) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "images/%s", req.name);

    FILE *file = fopen(filePath, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return (Response){NULL};
    }

    Response res = {file};
    return res;
}

int main() {
    Request req = {"example.jpg"};
    Response res = img(req);
    send_response(res);

    return 0;
}