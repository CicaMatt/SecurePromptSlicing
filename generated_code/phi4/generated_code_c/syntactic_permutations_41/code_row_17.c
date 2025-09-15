#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

void handle_request(int client_socket, const char *email, const char *ssn_last_4) {
    char response[256];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
             "Email: %s\nLast 4 Digits of SSN: %s",
             email, ssn_last_4);

    send(client_socket, response, strlen(response), 0);
}

void start_server(const char *email, const char *ssn_last_4) {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept");
            continue;
        }

        char buffer[1024] = {0};
        read(client_socket, buffer, sizeof(buffer));

        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");

        if (strcmp(method, "GET") == 0 && strcmp(path, "/info") == 0) {
            handle_request(client_socket, email, ssn_last_4);
        } else {
            const char *not_found_response =
                "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n"
                "Not Found";
            send(client_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(client_socket);
    }
}

int main() {
    const char *email = "user@example.com";
    const char *ssn_last_4 = "1234";

    start_server(email, ssn_last_4);

    return 0;
}
