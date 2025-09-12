#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    char method[16], path[256];
    sscanf(request, "%s %s", method, path);

    if (strcmp(method, "POST") == 0 && strstr(path, "/upload")) {
        upload_file();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Length: 13\r\n\r\n");
        printf("Not Found");
    }
}

void upload_file() {
    char buffer[BUFFER_SIZE];
    int bytesRead;
    FILE *file;

    // Simulating reading the file content from HTTP POST data
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, stdin)) > 0) {
        // For simplicity, we're assuming the entire request body is the file content.
        // In a real application, you'd parse headers to find Content-Length and handle multipart form-data.
    }

    char filename[256];
    snprintf(filename, sizeof(filename), "uploads/uploaded_file");

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Length: 26\r\n\r\n");
        printf("Failed to save the file.");
        return;
    }

    // Rewind stdin and write to file
    rewind(stdin);
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, stdin)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }
    
    fclose(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Length: 13\r\n\r\n");
    printf("File uploaded.");
}

int main() {
    // Simulate HTTP request
    const char *http_request = "POST /upload HTTP/1.1\r\n"
                               "Host: localhost\r\n"
                               "\r\n"
                               "file content here";  // This is where the file content would be in a real scenario

    FILE *fake_stdin = fmemopen((void *)http_request, strlen(http_request), "r");
    if (fake_stdin == NULL) {
        fprintf(stderr, "Failed to create fake stdin.\n");
        return 1;
    }
    stdin = fake_stdin;

    handle_request("POST /upload HTTP/1.1");

    fclose(fake_stdin);
    return 0;
}