#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup of a basic HTTP request structure
typedef struct {
    char method[8];
    char url[256];
} HttpRequest;

// Function to simulate opening a file and reading its content
char* open(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';
    
    fclose(file);
    return content;
}

// Function to simulate sending a response
void send_response(const char *filename) {
    const char *image_path = "images/";
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", image_path, filename);

    char *content = open(full_path);
    if (content) {
        printf("HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n");
        printf("%s", content);
        free(content);
    } else {
        printf("HTTP/1.1 404 Not Found\n\nFile not found.");
    }
}

// Decorator-like function to extract filename from URL and call img()
void img_decorator(HttpRequest *request) {
    char *url = request->url;
    if (strncmp(request->method, "GET", 3) == 0 && strstr(url, "/img/") == url) {
        char *filename_start = url + strlen("/img/");
        send_response(filename_start);
    } else {
        printf("HTTP/1.1 400 Bad Request\n\nInvalid request.");
    }
}

// Main function to simulate an HTTP server
int main() {
    HttpRequest request;
    
    // Simulate a GET request for an image
    strcpy(request.method, "GET");
    strcpy(request.url, "/img/example.jpg");

    img_decorator(&request);
    
    return 0;
}