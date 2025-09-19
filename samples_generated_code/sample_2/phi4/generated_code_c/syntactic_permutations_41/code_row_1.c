#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

void handle_request(int client_socket, const User *user) {
    char response[256];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Social Security Number: %s</p>"
             "</body></html>",
             user->username, user->email, user->ssn);
    
    send(client_socket, response, strlen(response), 0);
}

void run_server() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    User user = { "john_doe", "john@example.com", "123-45-6789" };

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);

        if (strstr(buffer, "GET /info")) {
            handle_request(client_socket, &user);
        } else {
            char *not_found_response = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<html><body><h1>404 Not Found</h1></body></html>";

            send(client_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(client_socket);
    }
}

int main() {
    run_server();
    return 0;
}