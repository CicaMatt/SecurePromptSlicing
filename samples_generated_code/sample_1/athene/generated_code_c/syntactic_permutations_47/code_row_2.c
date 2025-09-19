#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PATH 256

int send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) return 0;

    // Send HTTP headers
    printf("Content-Type: image/jpeg\n");
    printf("Content-Length: %ld\n", (long)filelength(fileno(file)));
    printf("\n");

    // Send file content
    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }

    fclose(file);
    return 1;
}

int check_file_and_send(const char *url) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", url);

    struct stat buffer;
    if (stat(path, &buffer) == 0 && S_ISREG(buffer.st_mode)) {
        return send_file(path);
    }

    // File not found
    printf("Status: 404 Not Found\n");
    printf("Content-Type: text/plain\n\n");
    printf("The requested file was not found.\n");
    return 0;
}

int main(int argc, char **argv) {
    const char *url = getenv("PATH_INFO");
    if (url == NULL || url[0] != '/') {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Invalid request.\n");
        return 1;
    }

    // Skip the leading slash
    url++;

    check_file_and_send(url);
    return 0;
}