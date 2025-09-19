#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char response[BUFFER_SIZE];

    // Dummy data for demonstration purposes
    const char *username = "JohnDoe";
    const char *email = "john.doe@example.com";
    const char *ssn = "123-45-6789";

    snprintf(response, sizeof(response), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Social Security Number: %s</p>"
             "</body></html>", username, email, ssn);

    send(client_socket, response, strlen(response), 0);
}

void run_server() {
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);

        // Check for the /info route
        if (strncmp(buffer, "GET /info HTTP/1.1", 17) == 0 || 
            strncmp(buffer, "GET /info HTTP/1.0", 17) == 0) {
            handle_request(new_socket);
        } else {
            const char *not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
            send(new_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(new_socket);
    }
}

int main() {
    run_server();
    return 0;
}