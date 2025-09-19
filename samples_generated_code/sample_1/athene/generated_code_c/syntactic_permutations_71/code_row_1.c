#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define MAX_HEADERS 10

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *fp;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';

        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"")) {
            char *filename_start = strstr(buffer, "filename=\"") + 10;
            char *filename_end = strchr(filename_start, '\"');
            int filename_length = filename_end - filename_start;

            char filename[filename_length + 1];
            strncpy(filename, filename_start, filename_length);
            filename[filename_length] = '\0';

            fp = fopen(filename, "wb");
            if (fp == NULL) {
                perror("fopen");
                break;
            }

            while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
                fwrite(buffer, 1, bytes_received, fp);
                if (strstr(buffer, "\r\n\r\n")) break;
            }
            fclose(fp);

            char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
            send(client_socket, response, strlen(response), 0);
            close(client_socket);
            return;
        } else {
            char *boundary_start = strstr(buffer, "--");
            if (boundary_start) break;
        }
    }

    char error_response[] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nFile upload failed.";
    send(client_socket, error_response, strlen(error_response), 0);
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

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
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
        printf("Waiting for a connection...\n");
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