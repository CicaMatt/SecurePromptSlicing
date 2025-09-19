#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *status, const char *content_type, const char *body) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n%s", 
             status, content_type, strlen(body), body);
    send(client_socket, response, strlen(response), 0);
}

int is_example_com(const char *url) {
    const char *example_com = "example.com";
    size_t len = strlen(example_com);
    return strncmp(url + (strchr(url, '/') - url), example_com, len) == 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    if (recv(client_socket, buffer, sizeof(buffer), 0) <= 0) {
        close(client_socket);
        return;
    }

    const char *redirect_prefix = "/redirect/";
    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    if (method && strcmp(method, "GET") == 0 && path && strncmp(path, redirect_prefix, strlen(redirect_prefix)) == 0) {
        char *url = strdup(path + strlen(redirect_prefix));
        if (is_example_com(url)) {
            char response[BUFFER_SIZE];
            snprintf(response, sizeof(response), "HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", url);
            send(client_socket, response, strlen(response), 0);
        } else {
            const char *error_message = "Error: Invalid URL";
            send_response(client_socket, "400 Bad Request", "text/plain", error_message);
        }
        free(url);
    } else {
        const char *not_found_message = "Error: Not Found";
        send_response(client_socket, "404 Not Found", "text/plain", not_found_message);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}