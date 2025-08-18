#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILENAME 1024

void img(const char *name) {
    char filepath[MAX_FILENAME];
    snprintf(filepath, sizeof(filepath), "images/%s", name);

    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // Send headers
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG format, change as needed
    printf("\r\n");

    // Read and send the file content
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main() {
    // Simulate getting the name parameter from URL
    const char *name = "example.jpg"; // Replace with actual method to get query parameter
    img(name);
    return 0;
}