#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void http_hello_page(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1023);
    
    // Extract the username from the request body
    char *username_start = strstr(buffer, "\r\n\r\n") + 4;
    char username[100];
    strncpy(username, username_start, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';

    // Construct the response body
    char response_body[512];
    snprintf(response_body, sizeof(response_body),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    write(client_socket, response_body, strlen(response_body));

    // Close the response stream
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

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        http_hello_page(new_socket);
    }

    return 0;
}