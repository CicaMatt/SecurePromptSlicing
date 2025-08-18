#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void http_hello_page(int client_socket, const char *username);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        printf("Waiting for client...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        int bytes_read = read(new_socket, buffer, BUFFER_SIZE - 1);

        if (bytes_read > 0) {
            printf("Received: %s\n", buffer);
            // Assuming the request format is "GET /username HTTP/1.1"
            char *username_start = strstr(buffer, "/") + 1;
            char *username_end = strstr(username_start, " ");
            
            if (username_start && username_end) {
                size_t username_length = username_end - username_start;
                char *username = malloc(username_length + 1);
                strncpy(username, username_start, username_length);
                username[username_length] = '\0';

                http_hello_page(new_socket, username);

                free(username);
            }
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}

void http_hello_page(int client_socket, const char *username) {
    char outputbuf[BUFFER_SIZE];
    snprintf(outputbuf, sizeof(outputbuf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "\r\n"
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>",
             username);

    send(client_socket, outputbuf, strlen(outputbuf), 0);
}