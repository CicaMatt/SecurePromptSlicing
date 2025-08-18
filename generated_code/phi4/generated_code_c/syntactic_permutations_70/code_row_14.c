#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_http_request(const char *request);
void process_post_data(const char *data, size_t length);

int main() {
    char buffer[BUFFER_SIZE];
    
    printf("Simple Web Server\n");
    
    while (1) {
        // Simulate reading an HTTP request from a client
        memset(buffer, 0, BUFFER_SIZE);
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        handle_http_request(buffer);
    }

    return 0;
}

void handle_http_request(const char *request) {
    const char *method = "POST";
    const char *boundary_prefix = "--";

    if (strstr(request, method)) {
        size_t len = strlen(request);
        const char *boundary_start = strstr(request, boundary_prefix);

        if (boundary_start) {
            // Extract boundary
            char boundary[256];
            sscanf(boundary_start, "%*[^0-9]%255s", boundary);

            // Locate content after headers
            const char *content_start = strstr(request, "\r\n\r\n") + 4;

            if (content_start) {
                process_post_data(content_start, strlen(content_start));
            }
        }
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\r\n");
        printf("Content-Length: 0\r\n");
        printf("\r\n");
    }
}

void process_post_data(const char *data, size_t length) {
    const char *boundary = strstr(data, "\r\n") + 2; // Skip the first line

    FILE *file;
    char filename[256] = "uploads/file";
    file = fopen(filename, "wb");

    if (file == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Length: 0\r\n");
        printf("\r\n");
        return;
    }

    const char *start = data + strlen(boundary);
    while ((strstr(start, boundary)) && (strlen(boundary) > 0)) {
        start += strlen(boundary) + 4; // Skip the boundary line
        const char *name_start = strstr(start, "filename=\"") + 10;
        const char *name_end = strstr(name_start, "\"\r\n");
        if (name_end != NULL) {
            strncpy(filename + 9, name_start, name_end - name_start);
            filename[name_end - name_start + 9] = '\0';
        }
        
        start += strlen("\r\n\r\n"); // Skip headers
        const char *end_boundary = strstr(start, "\r\n" boundary_prefix);

        if (end_boundary) {
            size_t file_content_length = end_boundary - start;
            fwrite(start, sizeof(char), file_content_length, file);
            start = end_boundary + strlen("\r\n");
        } else {
            break; // No more boundaries
        }
    }

    fclose(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Length: 0\r\n");
    printf("\r\n");

    printf("File uploaded successfully.\n");
}


To run this code, ensure that a directory named `uploads` exists in the same location as the executable. This simple web server reads input from standard input (simulating an HTTP request) and writes output to standard output (acting as an HTTP response). It handles file uploads by parsing multipart/form-data requests, extracting filenames, and saving uploaded files into the `uploads/` directory.