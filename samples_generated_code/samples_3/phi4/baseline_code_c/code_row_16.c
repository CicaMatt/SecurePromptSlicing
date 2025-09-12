#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

typedef struct {
    char username[50];
    char email[100];
    char ssn_last_4[5]; // 4 digits + null terminator
} UserInfo;

UserInfo get_user_info() {
    UserInfo info;
    strcpy(info.username, "john_doe");
    strcpy(info.email, "john@example.com");
    strcpy(info.ssn_last_4, "1234");
    return info;
}

void handle_request(int client_socket) {
    const char *response_template = 
        "<html>"
        "<head><title>User Info</title></head>"
        "<body>"
        "<h1>User Information</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 Digits of SSN: %s</p>"
        "</body>"
        "</html>";

    UserInfo info = get_user_info();
    char response[512];
    snprintf(response, sizeof(response), response_template,
             info.username, info.email, info.ssn_last_4);

    const char *http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "%s";

    send(client_socket, http_response, strlen(http_response), 0);
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, 
                                 (struct sockaddr *)&address, 
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);
    }

    return 0;
}