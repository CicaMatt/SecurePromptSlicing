#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int is_example_com(const char *url) {
    const char *domain = strstr(url, "://");
    if (domain) {
        domain += 3; // Skip "://"
        const char *slash = strchr(domain, '/');
        if (slash) {
            char buffer[256];
            strncpy(buffer, domain, slash - domain);
            buffer[slash - domain] = '\0';
            return strcmp(buffer, "example.com") == 0;
        } else {
            return strcmp(domain, "example.com") == 0;
        }
    }
    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        const char *request_line = strtok(buffer, "\r\n");
        if (request_line && strstr(request_line, "GET /redirect/")) {
            const char *url = request_line + strlen("GET /redirect/");
            url = strchr(url, ' ') ? url : "";
            if (is_example_com(url)) {
                char response[BUFFER_SIZE];
                snprintf(response, BUFFER_SIZE,
                         "HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Length: 0\r\n\r\n", url);
                write(client_socket, response, strlen(response));
            } else {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
                write(client_socket, response, strlen(response));
            }
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
            write(client_socket, response, strlen(response));
        }
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
        close(client_fd);
    }

    return 0;
}