#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char* (*handler)(char*);
} Route;

char* handle_image_request(char* filename) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", filename);
    
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return "File not found";
    } else {
        fclose(file);
        return "File found and sent";
    }
}

char* route_handler(char* url) {
    char filename[MAX_PATH];
    sscanf(url, "/image/%s", filename);
    return handle_image_request(filename);
}

int main() {
    Route route = { .handler = route_handler };
    
    // Simulate a URL request
    char* url = "/image/example.jpg";
    char* response = route.handler(url);
    printf("%s\n", response);

    return 0;
}