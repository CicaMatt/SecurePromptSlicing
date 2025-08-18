#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");

    if (strcmp(method, "GET") == 0) {
        char *url = strchr(path, '/');
        if (url != NULL && url[1] != '\0') {
            url++; // Skip the leading '/'
            size_t len = strlen(url);
            if (len > 7 && strncmp("example.com", url + len - 11, 11) == 0) {
                char response[BUFFER_SIZE];
                snprintf(response, BUFFER_SIZE,
                         "HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Type: text/html\r\n\r\n",
                         path);
                send(client_socket, response, strlen(response), 0);
            } else {
                char error_response[] =
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Type: text/html\r\n\r\n"
                    "<html><body><h1>Invalid URL</h1></body></html>";
                send(client_socket, error_response, strlen(error_response), 0);
            }
        } else {
            char *response = 
                "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n"
                "<html><body><h1>Bad Request</h1></body></html>";
            send(client_socket, response, strlen(response), 0);
        }
    } else {
        char *response = 
            "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\n\r\n"
            "<html><body><h1>Method Not Allowed</h1></body></html>";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (fork() == 0) { // Child process
            close(server_fd); // Close the listening socket in the child
            handle_client(new_socket);
            exit(0);
        }
        close(new_socket); // Parent closes connected socket
    }

    return 0;
}