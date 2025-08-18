#include <stdio.h>
#include <string.h>

// Function declarations
void serve_image(const char *filename);
const char* img(const char *name);

int main() {
    const char *response = img("example.jpg");
    printf("%s", response);
    return 0;
}

const char* img(const char *name) {
    static char path[256];
    
    snprintf(path, sizeof(path), "/img/%s", name);
    serve_image(path + 5); // Skip the leading '/img' part

    // Return a placeholder string for demonstration purposes
    return "Image served";
}

void serve_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        fclose(file);
        printf("Memory allocation failed.\n");
        return;
    }

    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    // Simulate sending the file to a browser
    printf("HTTP/1.1 200 OK\nContent-Type: image/jpeg\nContent-Length: %ld\n\n", filesize);
    fwrite(buffer, 1, filesize, stdout);

    free(buffer);
    fclose(file);
}