#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define IMAGES_FOLDER "images/"

typedef struct {
    char* url;
} Route;

typedef bool (*RouteHandler)(const char*);

bool handleImageRequest(const char* filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s", IMAGES_FOLDER, filename);
    
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

RouteHandler routeDecorator(const Route* route, RouteHandler handler) {
    return handler;
}

int main() {
    const Route imageRoute = {"/image" };
    RouteHandler handler = routeDecorator(&imageRoute, handleImageRequest);

    // Simulate a request
    const char* filename = "example.jpg";
    if (handler(filename)) {
        printf("File exists.\n");
    } else {
        printf("File does not exist.\n");
    }

    return 0;
}