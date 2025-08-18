#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define BACKLOG 10
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    FILE *fp;

    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "POST") && strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=")) {
            char *filename = strstr(buffer, "filename=\"") + strlen("filename=\"");
            filename[strcspn(filename, "\"")] = '\0';
            fp = fopen(filename, "wb");

            if (fp == NULL) {
                send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 36\r\nConnection: close\r\n\r\nFailed to create file on server.", 97, 0);
                return;
            }

            char *data_start = strstr(buffer, "\r\n\r\n") + strlen("\r\n\r\n");
            fwrite(data_start, 1, bytes_read - (data_start - buffer), fp);

            while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                fwrite(buffer, 1, bytes_read, fp);
                if (strstr(buffer, "\r\n--") != NULL) break;
            }

            fclose(fp);
            send(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 29\r\nConnection: close\r\n\r\nFile uploaded successfully.", 85, 0);
        } else {
            const char *response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 34\r\nConnection: close\r\n\r\nMethod not allowed for this resource.";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }

        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}