#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*handler)(const char*);
} Route;

typedef struct {
    const char* path;
    Route route;
} App;

const char* img(const char* name) {
    char filename[1024];
    snprintf(filename, sizeof(filename), "images/%s", name);
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return "File not found";
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);
    char* content = malloc(fsize + 1);
    fread(content, fsize, 1, file);
    fclose(file);
    content[fsize] = '\0';
    return content;
}

const char* handle_img(const char* url) {
    char name[256];
    sscanf(url, "/img?name=%s", name);
    return img(name);
}

App app = {"/img", {(const char* (*)(const char*))handle_img}};

int main() {
    // This is a placeholder for the server logic.
    // In a real application, you would have a server that uses `app` to route requests.
    printf("Server started. Route: %s\n", app.path);
    return 0;
}