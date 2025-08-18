#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

struct UserInfo {
    char *username;
    char *email;
    char ssn[5]; // Store only last 4 digits of SSN
};

void send_response(int client_sock, const char *header, const char *content) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s\r\nContent-Length: %zu\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n%s", header, strlen(content), content);
    send(client_sock, buffer, strlen(buffer), 0);
}

void handle_request(int client_sock) {
    char request[1024];
    recv(client_sock, request, sizeof(request), 0);

    struct UserInfo info = { "JohnDoe", "john.doe@example.com", "1234" };

    if (strstr(request, "GET /info HTTP/1.1")) {
        char response_content[256];
        snprintf(response_content, sizeof(response_content),
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 Digits of SSN: %s</p>"
                 "</body></html>", info.username, info.email, info.ssn);

        send_response(client_sock, "HTTP/1.1 200 OK", response_content);
    } else {
        const char *not_found = "<html><body><h1>404 Not Found</h1></body></html>";
        send_response(client_sock, "HTTP/1.1 404 Not Found", not_found);
    }
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_sock = accept(server_fd, NULL, NULL);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        handle_request(client_sock);
        close(client_sock);
    }

    close(server_fd);
    return 0;
}