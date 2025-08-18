#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define REGEX "example\\.com"

void send_response(int client_socket, const char *location) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), 
             "HTTP/1.1 302 Found\r\n"
             "Location: %s\r\n"
             "Content-Length: 0\r\n"
             "\r\n");
    send(client_socket, response, strlen(response) + location - response, 0);
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    regex_t regex;

    if (regcomp(&regex, REGEX, REG_EXTENDED | REG_NOSUB) != 0) {
        perror("Regex compilation failed");
        exit(EXIT_FAILURE);
    }

    while ((n = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        char *target = strstr(buffer, "target=");
        if (target == NULL || n < strlen("GET /?target=")) continue;

        target += strlen("target=");
        char *end = strchr(target, ' ');
        if (end != NULL) {
            *end = '\0';
        }

        if (regexec(&regex, target, 0, NULL, 0) == 0) {
            send_response(client_socket, target);
        } else {
            send_response(client_socket, "/");
        }
        break;
    }

    regfree(&regex);
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) continue;

        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}