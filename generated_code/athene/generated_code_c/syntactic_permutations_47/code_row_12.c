#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PATH 256

typedef int (*handler_t)(const char *url, const char *filename);

int send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return -1;

    // Simulate sending file to browser
    printf("Sending file %s to browser...\n", filename);
    fclose(file);
    return 0;
}

int route_handler(const char *url, const char *filename) {
    struct stat buffer;
    int exists = stat(filename, &buffer) == 0;

    if (exists) {
        return send_file_to_browser(filename);
    } else {
        printf("File %s not found.\n", filename);
        return -1;
    }
}

int route(const char *url, const char *filename, handler_t handler) {
    char full_path[MAX_PATH];
    snprintf(full_path, MAX_PATH, "./%s", filename);

    return handler(url, full_path);
}

int main() {
    const char *url = "/example";
    const char *filename = "example.html";

    route(url, filename, route_handler);

    return 0;
}