#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int is_valid_url(const char *url) {
    if (strlen(url) > 7 && strncmp(url, "http://", 7) == 0) return 1;
    if (strlen(url) > 8 && strncmp(url, "https://", 8) == 0) return 1;
    return 0;
}

void send_response(int client_socket, const char *status, const char *content_type, const char *body) {
    char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE, 
             "HTTP/1.1 %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %zu\r\n"
             "\r\n"
             "%s",
             status, content_type, strlen(body), body);
    send(client_socket, response, strlen(response), 0);
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    if (recv(client_socket, buffer, BUFFER_SIZE - 1, 0) <= 0) return;

    char *url = NULL;
    if (strstr(buffer, "/redirect/") == buffer + 4) {
        url = strstr(buffer, "/redirect/") + 9;
        char *space = strchr(url, ' ');
        if (space) *space = '\0';
    }

    if (url && is_valid_url(url)) {
        char redirect_response[BUFFER_SIZE];
        snprintf(redirect_response, BUFFER_SIZE, "Location: %s\r\n", url);
        send_response(client_socket, "302 Found", "", redirect_response);
    } else {
        const char *error_message = "<h1>Invalid URL</h1>";
        send_response(client_socket, "400 Bad Request", "text/html", error_message);
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

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
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
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
        close(client_fd);
    }

    return 0;
}