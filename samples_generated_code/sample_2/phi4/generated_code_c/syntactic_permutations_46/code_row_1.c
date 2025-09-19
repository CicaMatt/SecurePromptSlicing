#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function prototype for handling HTTP requests
void handle_request(const char *request);

// Simulated img() function decorator association with URL /img
const char *img_url = "/img";

// Main function to simulate server behavior
int main() {
    const char *http_request =
        "GET /img?name=example.jpg HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "\r\n";
    
    handle_request(http_request);
    return 0;
}

void handle_request(const char *request) {
    char method[BUFFER_SIZE];
    char url[BUFFER_SIZE];
    char protocol[BUFFER_SIZE];

    // Extracting the method, URL and protocol from request
    sscanf(request, "%s %s %s", method, url, protocol);

    if (strcmp(method, "GET") == 0 && strstr(url, img_url) != NULL) {
        char *params = strchr(url, '?');
        if (params) {
            params++; // Skip the '?' character
            char filename[BUFFER_SIZE];
            sscanf(params, "name=%s", filename);

            FILE *file = fopen(filename, "rb");
            if (file) {
                printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");

                // Reading and sending file content
                char buffer[BUFFER_SIZE];
                size_t bytes_read;
                while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                    fwrite(buffer, 1, bytes_read, stdout);
                }
                
                fclose(file);
            } else {
                printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
            }
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad request.\n");
    }
}