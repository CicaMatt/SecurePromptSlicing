#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup for HTTP request handling (normally handled by a web server framework)
typedef struct {
    char method[10];
    char uri[256];
} HttpRequest;

typedef struct {
    FILE *file;
} HttpResponse;

void send_response(HttpResponse *response, const char *mime_type) {
    // Simulate sending the file as a response
    printf("Serving file with MIME type: %s\n", mime_type);
    if (response->file != NULL) {
        fseek(response->file, 0, SEEK_SET); // Reset to beginning of the file
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), response->file)) {
            printf("%s", buffer);
        }
        fclose(response->file);
    } else {
        printf("404 Not Found\n");
    }
}

void img(HttpRequest *request, HttpResponse *response) {
    const char *base_path = "/img";
    
    if (strncmp(request->method, "GET", 3) == 0 && strncmp(request->uri, base_path, strlen(base_path)) == 0) {
        char filename[256];
        snprintf(filename, sizeof(filename), "%s%s", "./images/", request->uri + strlen(base_path));
        
        response->file = fopen(filename, "rb");
        if (response->file != NULL) {
            send_response(response, "image/jpeg"); // Assuming JPEG for simplicity
        } else {
            printf("File not found\n");
            response->file = NULL; // Ensure file is set to NULL on error
        }
    } else {
        printf("Method Not Allowed or Incorrect URI\n");
    }
}

int main() {
    HttpRequest request = {"GET", "/img/example.jpg"};
    HttpResponse response = {NULL};
    
    img(&request, &response);
    
    return 0;
}