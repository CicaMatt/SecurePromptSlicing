#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define SAVE_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *file;
    char *boundary = NULL, *content_type = NULL, *filename = NULL;

    while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[n] = '\0';

        if (strstr(buffer, "Content-Type: multipart/form-data") != NULL) {
            content_type = strstr(buffer, "boundary=");
            boundary = strtok(content_type + 8, "\r\n");
        }

        if (filename == NULL && strstr(buffer, "filename=") != NULL) {
            char *temp = strstr(buffer, "filename=\"") + 10;
            filename = strtok(temp, "\"");
        }

        if (strstr(buffer, boundary) != NULL && filename != NULL) {
            file = fopen(SAVE_DIR "/" filename, "ab");

            if (file == NULL) {
                perror("Failed to open file");
                close(client_socket);
                return;
            }

            char *start_content = strstr(buffer, "\r\n\r\n") + 4;
            char *end_content = strstr(start_content, boundary);

            fwrite(start_content, 1, end_content - start_content - 2, file);
            fclose(file);
            filename = NULL;

            const char response[] =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "\r\n"
                "<html><body>File uploaded successfully.</body></html>";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (access(SAVE_DIR, F_OK) == -1) {
        mkdir(SAVE_DIR, 0755);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}