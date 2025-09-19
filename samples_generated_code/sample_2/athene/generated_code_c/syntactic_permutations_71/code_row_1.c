#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    FILE *file = NULL;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';

        if (strstr(buffer, "POST /upload") != NULL) {
            char filename[BUFFER_SIZE];
            sscanf(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]\"", filename);

            file = fopen(UPLOAD_DIR "/" filename, "wb");
            if (!file) {
                send(client_socket, "HTTP/1.1 500 Internal Server Error\r\n", 34, 0);
                close(client_socket);
                return;
            }

            char *data_start = strstr(buffer, "\r\n\r\n") + 4;
            fwrite(data_start, 1, bytes_read - (data_start - buffer), file);

            while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
                buffer[bytes_read] = '\0';
                if (strstr(buffer, "--") != NULL) break;
                fwrite(buffer, 1, bytes_read, file);
            }
            fclose(file);
            send(client_socket, "HTTP/1.1 200 OK\r\n", 17, 0);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\n";
            send(client_socket, response, strlen(response), 0);
        }
        break;
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOAD_DIR, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create upload directory");
        return EXIT_FAILURE;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

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