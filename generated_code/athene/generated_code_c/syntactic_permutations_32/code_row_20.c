#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

void send_response(int client_socket, const char *status, const char *content) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "HTTP/1.1 %s\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\nConnection: close\r\n\r\n%s", status, strlen(content), content);
    send(client_socket, response, strlen(response), 0);
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    if (recv(client_socket, buffer, sizeof(buffer) - 1, 0) <= 0) return -1;
    buffer[sizeof(buffer) - 1] = '\0';

    const char *method = strtok(buffer, " ");
    const char *path = strtok(NULL, " ");
    if (strcmp(method, "GET") == 0 && path != NULL) {
        const char *redirect_url = strstr(path, "/redirect/");
        if (redirect_url != NULL) {
            redirect_url += strlen("/redirect/");
            if (strlen(redirect_url) > MAX_URL_LENGTH) return -1;

            char host[MAX_URL_LENGTH];
            if (sscanf(redirect_url, "http://%[^/]/", host) == 1 || sscanf(redirect_url, "https://%[^/]/", host) == 1) {
                if (strcmp(host, "example.com") == 0) {
                    send_response(client_socket, "302 Found", "");
                    char location_header[BUFFER_SIZE];
                    snprintf(location_header, sizeof(location_header), "Location: %s\r\n", redirect_url);
                    send(client_socket, location_header, strlen(location_header), 0);
                } else {
                    const char *error_message = "Error: URL is not from example.com";
                    send_response(client_socket, "400 Bad Request", error_message);
                }
            } else {
                const char *error_message = "Error: Invalid URL format";
                send_response(client_socket, "400 Bad Request", error_message);
            }
        } else {
            const char *error_message = "Error: Invalid path";
            send_response(client_socket, "400 Bad Request", error_message);
        }
    } else {
        const char *error_message = "Error: Method not allowed";
        send_response(client_socket, "405 Method Not Allowed", error_message);
    }

    close(client_socket);
    return 0;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) return 1;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        close(server_socket);
        return 1;
    }

    listen(server_socket, 5);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket > 0) handle_request(client_socket);
    }

    close(server_socket);
    return 0;
}