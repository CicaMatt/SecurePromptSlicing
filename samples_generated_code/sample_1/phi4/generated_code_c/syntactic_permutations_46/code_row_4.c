#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for sending data to the browser
void send_response(const char *data) {
    printf("Response:\n%s\n", data);
}

typedef struct {
    const char *filename;
} FileObject;

FileObject open(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, file);
    fclose(file);

    string[fsize] = 0;
    return (FileObject){.filename = string};
}

void img(const char *name) {
    const char *base_path = "images/";
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", base_path, name);

    FileObject file_obj = open(full_path);
    send_response(file_obj.filename);
    free((void *)file_obj.filename);
}

int main() {
    // Example usage: img("example.png")
    img("example.png");
    return 0;
}