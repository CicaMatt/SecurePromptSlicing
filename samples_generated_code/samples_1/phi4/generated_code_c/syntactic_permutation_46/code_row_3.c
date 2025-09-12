#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void send_response(FILE *file, const char *content_type) {
    printf("Content-Type: %s\n", content_type);
    printf("\n");
    
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
}

void handle_request(const char *url) {
    const char *base_url = "/img";
    if (strncmp(url, base_url, strlen(base_url)) == 0) {
        size_t name_start_index = strlen(base_url);
        
        if (name_start_index < strlen(url)) {
            char *name = &url[name_start_index];
            FILE *file = fopen(name, "rb");
            
            if (file != NULL) {
                send_response(file, "image/jpeg"); // Assuming the images are JPEGs
                fclose(file);
            } else {
                printf("Content-Type: text/html\n\n");
                printf("<html><body><h1>404 Not Found</h1></body></html>");
            }
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body><h1>400 Bad Request</h1></body></html>");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}