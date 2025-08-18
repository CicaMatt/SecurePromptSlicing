#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

int check_file_exists(const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void handle_request(const char *url) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", url);

    if (check_file_exists(path)) {
        printf("File exists: %s\n", path);
        // Additional logic to serve the file can be added here
    } else {
        printf("File does not exist: %s\n", path);
    }
}

int main() {
    const char *url = "example.jpg"; // This would normally come from a request
    handle_request(url);
    return 0;
}