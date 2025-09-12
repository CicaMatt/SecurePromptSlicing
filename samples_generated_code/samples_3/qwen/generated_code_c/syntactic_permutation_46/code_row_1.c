#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    struct stat st;
    if (fstat(fileno(file), &st) != 0) {
        perror("Failed to get file stats");
        fclose(file);
        return;
    }

    printf("Content-Length: %ld\r\n", st.st_size);
    printf("Content-Type: image/jpeg\r\n"); // Adjust content type as needed
    printf("\r\n");

    char buffer[4096];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, nread, stdout);
    }

    fclose(file);
}

void img(const char *name) {
    if (!name || strlen(name) == 0) {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("No image name provided.\n");
        return;
    }

    char filename[256];
    snprintf(filename, sizeof(filename), "images/%s", name);

    struct stat st;
    if (stat(filename, &st) != 0 || !S_ISREG(st.st_mode)) {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\n");
        return;
    }

    send_file(filename);
}

int main() {
    const char *name = "example.jpg"; // This would normally be extracted from the URL
    img(name);
    return 0;
}