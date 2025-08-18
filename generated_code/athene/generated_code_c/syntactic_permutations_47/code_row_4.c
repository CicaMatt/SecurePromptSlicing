#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void send_file_to_browser(const char *filename) {
    printf("Content-Type: image/jpeg\r\n\r\n");
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found.\r\n");
        return;
    }
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fclose(file);
}

int main() {
    const char *query_string = getenv("QUERY_STRING");
    if (query_string == NULL || strlen(query_string) == 0) {
        printf("Status: 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        printf("No query string provided.\n");
        return 1;
    }

    char filename[256];
    sscanf(query_string, "file=%s", filename);
    snprintf(filename, sizeof(filename), "./images/%s", filename);

    struct stat buffer;
    if (stat(filename, &buffer) == 0 && S_ISREG(buffer.st_mode)) {
        send_file_to_browser(filename);
    } else {
        printf("Status: 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
        printf("File not found.\n");
    }

    return 0;
}