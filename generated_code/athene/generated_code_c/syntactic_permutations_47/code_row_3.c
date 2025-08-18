#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256
#define IMAGES_FOLDER "images/"

typedef struct {
    char* (*handler)(char*);
} Route;

char* serve_image(char* filename) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "%s%s", IMAGES_FOLDER, filename);

    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        return "File not found";
    }

    fclose(file);
    return "Image served successfully";
}

char* route_handler(char* url) {
    char* token = strtok(url, "/");
    if (token && strcmp(token, "image") == 0) {
        token = strtok(NULL, "/");
        if (token) {
            return serve_image(token);
        }
    }
    return "Invalid URL";
}

int main() {
    Route route = { .handler = route_handler };
    
    char* url = "/image/example.jpg"; // Example URL
    char* result = route.handler(url);
    printf("%s\n", result);

    return 0;
}