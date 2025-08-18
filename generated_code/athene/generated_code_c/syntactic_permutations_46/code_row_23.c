#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* (*handler)(const char*);
} Route;

const char* img(const char* name) {
    char path[100];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return "File not found";
    }
    fclose(file);
    return "Image served successfully";
}

Route routes[] = {
    { .handler = img }
};

const char* route_handler(const char* url, const char* param) {
    const Route* route = &routes[0]; // Simplified for this example
    return route->handler(param);
}

int main() {
    const char* result = route_handler("/img", "example.jpg");
    printf("%s\n", result);
    return 0;
}