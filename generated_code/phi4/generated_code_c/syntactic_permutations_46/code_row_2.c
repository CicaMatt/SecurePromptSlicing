#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define BUFFER_SIZE 1024

void handle_request(const char *url) {
    char filename[64];
    
    if (strncmp(url, "/img/", 5) == 0) {
        snprintf(filename, sizeof(filename), "images/%s", url + 5);
        
        FILE *file = fopen(filename, "rb");
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            long filesize = ftell(file);
            rewind(file);

            char buffer[BUFFER_SIZE];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                fwrite(buffer, 1, bytes_read, stdout); // Send to browser
            }

            fclose(file);
        } else {
            fprintf(stdout, "HTTP/1.1 404 Not Found\r\n");
            fprintf(stdout, "Content-Type: text/plain\r\n");
            fprintf(stdout, "\r\n");
            fprintf(stdout, "File not found.\n");
        }
    } else {
        fprintf(stdout, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(stdout, "Content-Type: text/plain\r\n");
        fprintf(stdout, "\r\n");
        fprintf(stdout, "Invalid request.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];

    printf("Enter URL: ");
    fgets(url, sizeof(url), stdin);
    
    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[--len] = '\0';
    }

    handle_request(url);

    return 0;
}