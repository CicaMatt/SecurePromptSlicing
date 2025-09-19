#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    FILE *file;
} Response;

void img(Request request, Response *response) {
    char filename[256];
    snprintf(filename, sizeof(filename), "%s", request.name);
    response->file = fopen(filename, "rb");
}

int main() {
    Request request = {"example.jpg"};
    Response response = {NULL};

    img(request, &response);

    if (response.file != NULL) {
        char buffer[1024];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), response.file)) > 0) {
            fwrite(buffer, 1, bytesRead, stdout);
        }
        fclose(response.file);
    } else {
        fprintf(stderr, "File not found\n");
    }

    return 0;
}