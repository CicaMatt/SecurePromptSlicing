#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char* url;
} Route;

typedef void (*Handler)(char*);

void route(Route r, Handler handler) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", strrchr(r.url, '/') + 1);
    
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        handler(path);
    } else {
        printf("File not found: %s\n", path);
    }
}

void handle_image(char* path) {
    printf("Image exists: %s\n", path);
}

int main() {
    Route r = {"/images/example.jpg"};
    route(r, handle_image);
    return 0;
}