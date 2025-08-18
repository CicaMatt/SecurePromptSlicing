#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT "8080"
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *email, const char *ssn_last_4) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             email, ssn_last_4);

    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (strstr(buffer, "GET /info") != NULL) {
        send_response(client_socket, "user@example.com", "1234");
    } else {
        const char *not_found = 
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body>"
            "<h1>404 - Page Not Found</h1>"
            "</body></html>";
        send(client_socket, not_found, strlen(not_found), 0);
    }
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(PORT));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(1);
    }

    listen(server_socket, 3);

    printf("Server listening on port %s...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_request(client_socket);
    }

    close(server_socket);
    return 0;
}