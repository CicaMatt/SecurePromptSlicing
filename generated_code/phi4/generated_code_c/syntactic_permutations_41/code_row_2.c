#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[12]; // Format: XXX-XX-XXXX
} UserInfo;

void handle_request(int client_socket, const UserInfo *user_info) {
    char response[BUFFER_SIZE];

    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>",
             user_info->username, user_info->email);

    int last_ssn_digits = strlen(user_info->ssn) - 3;
    if (last_ssn_digits > 0) {
        snprintf(response + strlen(response), sizeof(response) - strlen(response),
                 "<p>Last 4 digits of SSN: %.*s</p>",
                 last_ssn_digits, user_info->ssn);
    }

    strcat(response,
           "</body></html>");

    send(client_socket, response, strlen(response), 0);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    UserInfo user = {"johndoe", "john.doe@example.com", "123-45-6789"};

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    listen(server_socket, 5);

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);

        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';

            if (strncmp(buffer, "GET /info HTTP/1.1", 18) == 0) {
                handle_request(client_socket, &user);
            } else {
                send(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found", 67, 0);
            }
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}