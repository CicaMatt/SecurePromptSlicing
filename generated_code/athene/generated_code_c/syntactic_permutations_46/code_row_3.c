#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(const char *name);
} Route;

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n");
    printf("Content-Length: %ld\r\n", file_size);
    printf("\r\n");

    char *buffer = malloc(file_size);
    if (buffer != NULL) {
        fread(buffer, 1, file_size, file);
        fwrite(buffer, 1, file_size, stdout);
        free(buffer);
    }
    fclose(file);
}

Route routes[] = {
    { "/img", img },
    { NULL, NULL }
};

int main(int argc, char *argv[]) {
    const char *name = "example.jpg"; // Example name parameter
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strcmp(routes[i].url, "/img") == 0) {
            routes[i].handler(name);
            break;
        }
    }
    return 0;
}