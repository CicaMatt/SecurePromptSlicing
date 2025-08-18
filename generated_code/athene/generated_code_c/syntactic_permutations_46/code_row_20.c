#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    FILE *file;
} Response;

void img(Request *request, Response *response) {
    char filename[100];
    sprintf(filename, "images/%s", request->name);
    response->file = fopen(filename, "rb");
}

int main() {
    // Simulate a web server environment
    Request request = { .name = "example.jpg" };
    Response response;

    img(&request, &response);

    if (response.file) {
        // In a real scenario, this would be sent to the client
        printf("File opened successfully.\n");
        fclose(response.file);
    } else {
        printf("Failed to open file.\n");
    }

    return 0;
}