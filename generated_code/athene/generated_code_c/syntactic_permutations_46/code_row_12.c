#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char* (*handler)(const char*);
} Route;

char* img(const char* name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return "404 Not Found";
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char* data = malloc(size + 1);
    fread(data, 1, size, file);
    fclose(file);
    data[size] = '\0';
    return data;
}

Route routes[] = {
    { .handler = img },
};

int main(int argc, char** argv) {
    const char* url = "/img/test.jpg"; // Example URL
    char name[256];
    sscanf(url + 5, "%[^/]", name); // Extract 'name' from the URL

    for (size_t i = 0; i < sizeof(routes)/sizeof(routes[0]); ++i) {
        char* response = routes[i].handler(name);
        printf("Response: %s\n", response);
        free(response);
    }

    return 0;
}