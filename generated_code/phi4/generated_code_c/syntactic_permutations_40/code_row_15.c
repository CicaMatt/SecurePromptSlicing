#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_four;
} Session;

Session session = { .username = "user123", .email = "user@example.com", .ssn_last_four = "6789" };

void info() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);
    printf("<p>Last 4 Digits of SSN: %s</p>", session.ssn_last_four);
    printf("</body></html>");
}

int handle_request(const char *request_path) {
    if (strcmp(request_path, "/info") == 0) {
        info();
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    const char *server_port = "8080";
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(server_port));

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %s\n", server_port);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, sizeof(buffer));
        printf("%s\n", buffer);

        const char *request_line = strtok(buffer, "\r\n");
        if (request_line) {
            char method[10], path[100];
            sscanf(request_line, "%s %s HTTP/1.1", method, path);
            if (handle_request(path)) {
                send(new_socket, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n"), 0);
            } else {
                char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
                send(new_socket, response, strlen(response), 0);
            }
        }

        close(new_socket);
    }

    return 0;
}