#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void handle_client(int client_fd) {
    char buffer[1024];
    const char response_template[] = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<html>\n"
        "<head><title>Info</title></head>\n"
        "<body>\n"
        "<h1>User Information</h1>\n"
        "<p>Username: JohnDoe</p>\n"
        "<p>Email: johndoe@example.com</p>\n"
        "<p>Last 4 SSN digits: 1234</p>\n"
        "</body>\n"
        "</html>";

    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        char *request_line = strtok(buffer, "\r\n");
        if (strncmp(request_line, "GET /info HTTP", 14) == 0) {
            write(client_fd, response_template, sizeof(response_template) - 1);
        } else {
            const char not_found[] =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                "<html>\n"
                "<head><title>Not Found</title></head>\n"
                "<body>\n"
                "<h1>404 - Page Not Found</h1>\n"
                "</body>\n"
                "</html>";
            write(client_fd, not_found, sizeof(not_found) - 1);
        }
    }

    close(client_fd);
}

void run_server(int port) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd >= 0) {
            handle_client(client_fd);
        } else {
            perror("accept");
        }
    }

    close(server_fd);
}

int main() {
    run_server(8080);
    return 0;
}