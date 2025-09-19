#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *url) {
    if (strncmp(url, "/img/", 5) == 0) {
        const char *filename = url + 5;
        FILE *file = fopen(filename, "rb");
        
        if (file == NULL) {
            printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
            return;
        }

        fseek(file, 0, SEEK_END);
        long fsize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *data = malloc(fsize + 1);
        if (data == NULL) {
            printf("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
            fclose(file);
            return;
        }

        fread(data, fsize, 1, file);
        data[fsize] = 0;

        fseek(file, 0, SEEK_SET);

        printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", fsize);
        
        while (fread(data, fsize, 1, file) == 1) {
            fwrite(data, fsize, 1, stdout);
        }

        free(data);
        fclose(file);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
    }
}

int main() {
    char buffer[BUFFER_SIZE];

    // Simulating a simple HTTP request
    snprintf(buffer, BUFFER_SIZE, "GET /img/example.jpg HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");

    // Extract the URL from the GET request
    char *url_start = strstr(buffer, "GET ") + 4;
    char *url_end = strstr(url_start, " ");
    if (url_end != NULL) {
        *url_end = '\0';
    }

    handle_request(url_start);

    return 0;
}


This C program is a basic implementation of handling an image request from a URL starting with `/img/`. It extracts the filename from the URL, attempts to open it as an image file, and sends its content back as an HTTP response. If any error occurs (e.g., file not found), appropriate HTTP status codes are returned. Note that this is a simple demonstration and lacks many features of a full-fledged web server or application framework.