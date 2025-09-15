#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function declarations
void handle_request(const char *request);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        handle_request(buffer);
    }

    fclose(file);
    return 0;
}

void handle_request(const char *request) {
    if (strncmp(request, "POST /upload", 12) == 0) {
        // Extracting content length
        const char *content_length_str = strstr(request, "Content-Length: ");
        if (!content_length_str) {
            printf("HTTP/1.1 400 Bad Request\r\n\r\n");
            return;
        }
        content_length_str += 16; // Move pointer to the start of the number

        size_t content_length = strtoul(content_length_str, NULL, 10);

        if (content_length > BUFFER_SIZE) {
            printf("HTTP/1.1 413 Payload Too Large\r\n\r\n");
            return;
        }

        char *file_content = malloc(content_length + 1);
        if (!file_content) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        
        // Read file content
        FILE *file = fopen("uploaded_file", "wb");
        if (!file) {
            perror("Error opening uploaded file for writing");
            free(file_content);
            exit(EXIT_FAILURE);
        }

        fread(file_content, 1, content_length, stdin);

        fwrite(file_content, 1, content_length, file);

        fclose(file);

        free(file_content);

        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.\n");
    } else {
        printf("HTTP/1.1 404 Not Found\r\n\r\n");
    }
}
