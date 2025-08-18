#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("HTTP/1.1 301 Moved Permanently\n");
        printf("Location: %s\n", url);
        printf("\n"); // End of headers
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Only example.com is allowed.\n");
    }
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    
    if (bytes_read > 0) {
        char *method = strtok(buffer, " ");
        char *url = strtok(NULL, " ");
        
        if (strcmp(method, "GET") == 0 && url != NULL) {
            redirect_invalid_url(url);
        } else {
            printf("HTTP/1.1 400 Bad Request\n");
            printf("Content-Type: text/plain\n");
            printf("\n");
            printf("Error: Invalid request method or missing URL.\n");
        }
    }

    close(client_socket);
}

int main(int argc, char *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

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

    printf("Server is listening on port 8080...\n");

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}