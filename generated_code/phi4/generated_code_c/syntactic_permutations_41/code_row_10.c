#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

void handle_request(const char *request, const char *username, const char *email, const char *ssn) {
    if (strstr(request, "GET /info")) {
        printf("HTTP/1.1 200 OK\r\n"
               "Content-Type: text/html; charset=UTF-8\r\n"
               "\r\n"
               "<html>\n"
               "<head><title>User Info</title></head>\n"
               "<body>\n"
               "<h1>User Information</h1>\n"
               "<p>Username: %s</p>\n"
               "<p>Email: %s</p>\n"
               "<p>Last 4 digits of SSN: %.*s</p>\n"
               "</body>\n"
               "</html>\n",
               username, email, 4, ssn + strlen(ssn) - 4);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nNot Found");
    }
}

int main() {
    const char *username = "john_doe";
    const char *email = "john.doe@example.com";
    const char *ssn = "123-45-6789";

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Cannot create socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Cannot bind");
        close(server_sock);
        return 1;
    }

    if (listen(server_sock, 10) < 0) {
        perror("Cannot listen");
        close(server_sock);
        return 1;
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Cannot accept connection");
            continue;
        }

        memset(buffer, 0, sizeof(buffer));
        read(client_sock, buffer, sizeof(buffer));

        handle_request(buffer, username, email, ssn);

        close(client_sock);
    }

    close(server_sock);
    return 0;
}