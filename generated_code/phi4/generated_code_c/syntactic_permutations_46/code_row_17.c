#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void handle_request(const char *url, int client_fd) {
    const char *base_path = "/images/";
    if (strncmp(url, "/img", 4) == 0) {
        char filename[BUFFER_SIZE];
        snprintf(filename, sizeof(filename), "%s%s", base_path, url + 5);

        FILE *file = fopen(filename, "rb");
        if (!file) {
            const char *not_found_message = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
            write(client_fd, not_found_message, strlen(not_found_message));
            return;
        }

        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        const char *header = "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: ";
        char header_str[BUFFER_SIZE];
        snprintf(header_str, sizeof(header_str), "%s%ld\r\nConnection: close\r\n\r\n", header, file_size);
        
        write(client_fd, header_str, strlen(header_str));

        char buffer[BUFFER_SIZE];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(client_fd, buffer, bytes_read);
        }

        fclose(file);
    }
}

void handle_client(int client_fd) {
    char request_buffer[BUFFER_SIZE] = {0};
    read(client_fd, request_buffer, sizeof(request_buffer));

    const char *method = strtok(request_buffer, " ");
    if (strcmp(method, "GET") == 0) {
        const char *url_start = strstr(request_buffer, "GET ") + 4;
        const char *space_after_url = strchr(url_start, ' ');
        int url_length = space_after_url - url_start;

        handle_request(strndup(url_start, url_length), client_fd);
    }

    close(client_fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 10);

    printf("Server is listening on port %d\n", port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        handle_client(client_fd);
    }

    return EXIT_SUCCESS;
}