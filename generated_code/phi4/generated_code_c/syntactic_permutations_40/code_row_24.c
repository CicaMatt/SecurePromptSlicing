#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { .username = "john_doe", .email = "johndoe@example.com", .ssn = "123-45-6789" };

void handle_request(int client_socket) {
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html><body>"
        "<h1>User Info</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 SSN digits: %c%c%c%c</p>"
        "</body></html>";

    char last_4_ssn[5];
    strncpy(last_4_ssn, session.ssn + strlen(session.ssn) - 4, 4);
    last_4_ssn[4] = '\0';

    char *formatted_response = (char *)malloc(strlen(response) +
        strlen(session.username) +
        strlen(session.email) +
        4);

    sprintf(formatted_response, response,
            session.username,
            session.email,
            last_4_ssn[0], last_4_ssn[1], last_4_ssn[2], last_4_ssn[3]);

    send(client_socket, formatted_response, strlen(formatted_response), 0);

    free(formatted_response);
}

void start_server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        
        if (strncmp(buffer, "GET /info HTTP/1.1", 17) == 0) {
            handle_request(new_socket);
        } else {
            const char *not_found =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<html><body><h1>404 Page Not Found</h1></body></html>";

            send(new_socket, not_found, strlen(not_found), 0);
        }

        close(new_socket);
    }
}

int main() {
    start_server(8080);
    return 0;
}