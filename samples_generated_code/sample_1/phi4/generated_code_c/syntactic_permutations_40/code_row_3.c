#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} session_data;

void handle_request(int client_socket) {
    const char response_template[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html><body>"
        "<h1>Session Information</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 SSN Digits: %s</p>"
        "</body></html>";

    // Example session data
    session_data *session = (session_data *)malloc(sizeof(session_data));
    session->username = "john_doe";
    session->email = "john.doe@example.com";
    session->ssn_last_4 = "1234";

    char response[512];
    snprintf(response, sizeof(response), response_template,
             session->username, session->email, session->ssn_last_4);

    send(client_socket, response, strlen(response), 0);
    free(session);
}

void start_server() {
    int server_fd, new_socket;
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
    address.sin_port = htons(8080);

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

    printf("Listening on port 8080...\n");

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (fork() == 0) {
            close(server_fd);

            char buffer[1024] = {0};
            read(new_socket, buffer, 1024);
            
            if (strncmp(buffer, "GET /info ", 10) == 0) {
                handle_request(new_socket);
            } else {
                const char *response = 
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "\r\n"
                    "<html><body><h1>Not Found</h1></body></html>";
                send(new_socket, response, strlen(response), 0);
            }

            close(new_socket);
            exit(0);
        }
        close(new_socket);
    }
}

int main() {
    start_server();
    return 0;
}