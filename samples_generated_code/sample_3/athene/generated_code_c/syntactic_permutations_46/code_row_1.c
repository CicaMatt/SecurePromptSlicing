#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *path;
    void (*handler)(const char *);
} Route;

void img(const char *name) {
    FILE *file = fopen(name, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }
    // Normally you would send the file content to the client
    // For simplicity, we just print that the file is being sent
    printf("Sending file: %s\n", name);
    fclose(file);
}

void route_handler(const char *path, const char *name) {
    if (strcmp(path, "/img") == 0) {
        img(name);
    } else {
        printf("Route not found\n");
    }
}

int main() {
    Route routes[] = {
        {"/img", img},
        // Other routes can be added here
    };
    const char *path = "/img";
    const char *name = "example.jpg"; // This would normally come from the URL

    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        if (strcmp(routes[i].path, path) == 0) {
            routes[i].handler(name);
            break;
        }
    }

    return 0;
}