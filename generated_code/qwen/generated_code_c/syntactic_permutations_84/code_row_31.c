#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    const char *error_message = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: ";
    const char *payload_not_found = "Payload parameter not found.";
    const char *type_create_error = "Payload type Create is not allowed.";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting up server address struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        // Accepting a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, error_message, strlen(error_message), 0);
            send(new_socket, payload_not_found, strlen(payload_not_found), 0);
        } else {
            // Move pointer to the start of the actual value
            payload_start += 8;

            char *end_of_payload = strchr(payload_start, '&');
            if (!end_of_payload) {
                end_of_payload = strchr(payload_start, ' ');
            }
            if (end_of_payload) {
                *end_of_payload = '\0';
            }

            // Check if the payload is of type Create
            if (strcmp(payload_start, "Create") == 0) {
                send(new_socket, error_message, strlen(error_message), 0);
                send(new_socket, type_create_error, strlen(type_create_error), 0);
            } else {
                send(new_socket, hello, strlen(hello), 0);
                send(new_socket, buffer, strlen(buffer), 0);
            }
        }

        close(new_socket);
    }

    return 0;
}