#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void send_file(FILE *file) {
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Send HTTP headers for image file
    printf("HTTP/1.0 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n");
    printf("\r\n");

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
}

void handle_request(const char *url) {
    // Check if URL starts with /img/
    if (strncmp(url, "/img/", 5) == 0) {
        const char *filename = url + 5; // Get the filename part of the URL

        // Open file in binary mode
        FILE *file = fopen(filename, "rb");
        if (file != NULL) {
            send_file(file);
            fclose(file);
        } else {
            // Handle file not found
            printf("HTTP/1.0 404 Not Found\r\n");
            printf("\r\n");
        }
    } else {
        // Handle other URLs
        printf("HTTP/1.0 400 Bad Request\r\n");
        printf("\r\n");
    }
}

int main() {
    char buffer[BUFFER_SIZE];

    // Read the request from standard input (stdin)
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        // Extract the URL part of the HTTP GET request
        char *method = strtok(buffer, " ");
        char *url = strtok(NULL, " ");

        if (method && url && strcmp(method, "GET") == 0) {
            handle_request(url);
        } else {
            printf("HTTP/1.0 400 Bad Request\r\n");
            printf("\r\n");
        }
    }

    return 0;
}