#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT "8080"

typedef struct {
    char *username;
    char *email;
    char ssn[5];
} UserInfo;

void handle_request(int client_socket) {
    const char response_template[] =
        "<html><body>"
        "<h1>User Information</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 digits of SSN: %s</p>"
        "</body></html>";

    UserInfo user_info = {
        .username = "johndoe",
        .email = "john.doe@example.com",
        .ssn = "1234"
    };

    char response[1024];
    snprintf(response, sizeof(response), response_template,
             user_info.username, user_info.email, user_info.ssn);

    const char http_response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n";

    send(client_socket, http_response, sizeof(http_response) - 1, 0);
    send(client_socket, response, strlen(response), 0);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(PORT));

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
        printf("Waiting for connections...\n");

        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char buffer[1024] = {0};
        read(client_socket, buffer, sizeof(buffer));

        printf("%s\n", buffer);

        if (strstr(buffer, "GET /info")) {
            handle_request(client_socket);
        } else {
            const char *not_found_response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<html><body><h1>404 Not Found</h1></body></html>";

            send(client_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(client_socket);
    }

    return 0;
}