#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock of sending data directly to browser (for demonstration purposes)
void send_to_browser(const char *data, size_t length) {
    fwrite(data, 1, length, stdout);
}

// Function simulating opening a file and reading it into memory
char* open_file(const char *filename, size_t *length) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    rewind(file);

    char *buffer = malloc(*length + 1);
    fread(buffer, 1, *length, file);
    fclose(file);

    buffer[*length] = '\0'; // Null-terminate for safety
    return buffer;
}

// Function to handle the image request and serve it
void img(const char *name) {
    const char *base_path = "./images/";
    size_t name_length = strlen(name);
    size_t path_length = strlen(base_path) + 1 + name_length;
    
    char full_path[path_length];
    snprintf(full_path, path_length, "%s%s", base_path, name);

    size_t content_length;
    char *file_content = open_file(full_path, &content_length);
    
    if (file_content) {
        send_to_browser(file_content, content_length);
        free(file_content);
    } else {
        const char *error_message = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        size_t error_length = strlen(error_message);
        send_to_browser(error_message, error_length);
    }
}

// Simulate handling an HTTP request
void handle_request(const char *request) {
    if (strstr(request, "GET /img")) {
        const char *start = strstr(request, "?name=") + 6;
        const char *end = strchr(start, ' ');
        size_t name_length = end ? end - start : strlen(start);

        char *name_buffer = malloc(name_length + 1);
        strncpy(name_buffer, start, name_length);
        name_buffer[name_length] = '\0';

        img(name_buffer);

        free(name_buffer);
    }
}

int main() {
    // Simulate an HTTP request to /img with a query parameter
    const char *http_request = "GET /img?name=test_image.jpg HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";

    handle_request(http_request);
    return 0;
}