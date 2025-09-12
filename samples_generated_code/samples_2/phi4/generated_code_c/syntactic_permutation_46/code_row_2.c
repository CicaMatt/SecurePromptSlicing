#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_img_request(const char *url, FILE *output) {
    const char *prefix = "/img/";
    if (strncmp(url, prefix, strlen(prefix)) != 0) {
        fprintf(output, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    // Extract the image name from the URL
    const char *image_name = url + strlen(prefix);
    
    // Open the requested image file
    FILE *file = fopen(image_name, "rb");
    if (!file) {
        fprintf(output, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    // Send HTTP headers for the image response
    fprintf(output, "HTTP/1.1 200 OK\r\n");
    fprintf(output, "Content-Type: ");
    
    if (strstr(image_name, ".jpg") || strstr(image_name, ".jpeg")) {
        fprintf(output, "image/jpeg\r\n");
    } else if (strstr(image_name, ".png")) {
        fprintf(output, "image/png\r\n");
    } else if (strstr(image_name, ".gif")) {
        fprintf(output, "image/gif\r\n");
    } else {
        fclose(file);
        fprintf(output, "text/plain\r\n"); // Default fallback
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    fprintf(output, "Content-Length: %ld\r\nConnection: close\r\n\r\n", file_size);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    // Send the image content
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(file);
}

int main() {
    const char *request_line = "GET /img/image.jpg HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    
    // Simulate reading the request line from a socket
    FILE *output = stdout;  // For demonstration, we'll write to standard output

    if (strncmp(request_line, "GET ", 4) == 0) {
        char url[256];
        sscanf(request_line, "GET %255s", url);
        
        handle_img_request(url, output);
    }

    return 0;
}