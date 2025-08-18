#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Read HTTP request headers and body from the socket
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';

        if (strstr(buffer, "Content-Length: ")) {
            char *content_length_str = strstr(buffer, "Content-Length: ");
            content_length_str += strlen("Content-Length: ");
            int content_length = atoi(content_length_str);
            
            // Read the file data from the socket
            char *file_data = malloc(content_length + 1);
            recv(client_socket, file_data, content_length, 0);
            file_data[content_length] = '\0';

            // Parse headers to get the filename (assuming a simple POST request)
            char *filename = NULL;
            char *tmp = strstr(buffer, "filename=\"");
            if (tmp) {
                tmp += strlen("filename=\"");
                char *end_quote = strchr(tmp, '\"');
                if (end_quote) {
                    int len = end_quote - tmp;
                    filename = malloc(len + 1);
                    strncpy(filename, tmp, len);
                    filename[len] = '\0';
                }
            }

            // Save the file to uploads directory
            if (filename) {
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "uploads/%s", filename);
                FILE *file = fopen(filepath, "wb");
                if (file) {
                    fwrite(file_data, 1, content_length, file);
                    fclose(file);
                }
                free(filename);
            }

            free(file_data);
        }

        memset(buffer, 0, BUFFER_SIZE);
    }
}

int main(int argc, char *argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind to port 8080
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // Accept a new connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == -1) {
            perror("accept");
            continue;
        }

        handle_request(client_socket);
        close(client_socket);
    }

    return 0;
}