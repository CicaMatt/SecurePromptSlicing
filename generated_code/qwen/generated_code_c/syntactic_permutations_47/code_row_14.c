#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void check_file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        printf("File exists: %s\n", filename);
        fclose(file);
    } else {
        perror("Error opening file");
    }
}

void route_decorator(const char *url_path, void (*func)(const char *)) {
    const char *base_path = "images/";
    char full_path[MAX_FILENAME_LENGTH];

    snprintf(full_path, sizeof(full_path), "%s%s", base_path, url_path);
    func(full_path);
}

int main() {
    route_decorator("example.jpg", check_file_exists);
    return 0;
}