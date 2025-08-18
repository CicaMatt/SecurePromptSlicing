#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void img(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    fread(buffer, size, 1, file);
    fclose(file);

    printf("%s", buffer);
    free(buffer);
}

int main() {
    // Simulating the request.args.get('file') by passing filename directly
    const char *filename = "example.jpg"; // This should be dynamically obtained from the URL in a real web server setup
    img(filename);
    return 0;
}