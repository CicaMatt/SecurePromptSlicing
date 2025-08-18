#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOADS_FOLDER "./uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        FILE *file;
        char filename[256] = "";
        sscanf(buffer, "POST /upload?filename=%s HTTP/1.1", filename);
        
        if (strlen(filename) > 0) {
            char filepath[512];
            snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_FOLDER, filename);
            file = fopen(filepath, "wb");

            if (file != NULL) {
                const char *boundary_start = "\r\n\r\n";
                const char *boundary_end = "\r\n--";
                char *start = strstr(buffer, boundary_start);
                if (start != NULL) {
                    start += strlen(boundary_start);
                    char *end = strstr(start, boundary_end);
                    if (end != NULL) {
                        fwrite(start, 1, end - start, file);
                    }
                }
                fclose(file);

                const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (access(UPLOADS_FOLDER, F_OK) == -1) {
        mkdir(UPLOADS_FOLDER, 0755);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Listening for connections on port %d...\n", PORT);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}