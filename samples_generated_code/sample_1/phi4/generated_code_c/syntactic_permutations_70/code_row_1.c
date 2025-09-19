#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    char method[10];
    char path[256];
    sscanf(request, "%s %s", method, path);

    if (strcmp(method, "POST") == 0 && strstr(path, "/upload")) {
        upload_file();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Length: 0\r\n\r\n");
    }
}

void upload_file() {
    char buffer[BUFFER_SIZE];
    FILE *file;
    
    // Read the request body (assuming it's a single line with the file content)
    fgets(buffer, BUFFER_SIZE, stdin);

    // Extract filename from Content-Disposition header (simplified parsing)
    char filename[256] = "uploaded_file";
    sscanf(buffer, "filename=\"%255[^"]\"", filename);

    // Save the uploaded file to the uploads directory
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "./uploads/%s", filename);

    file = fopen(filepath, "wb");
    if (file == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Length: 0\r\n\r\n");
        return;
    }

    // Read the remaining data and write to file
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, stdin)) > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }

    fclose(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Length: 0\r\n\r\n");
}

int main() {
    // Create uploads directory if it doesn't exist
    mkdir("./uploads", 0777);

    char request[BUFFER_SIZE];
    
    // Read the HTTP request
    fgets(request, BUFFER_SIZE, stdin);
    
    handle_request(request);

    return 0;
}