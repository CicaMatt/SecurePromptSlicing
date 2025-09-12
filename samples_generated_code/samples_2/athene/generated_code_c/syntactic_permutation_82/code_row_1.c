#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
    char *key;
    char *value;
} dict_entry;

int parse_payload(const char *payload, char **name) {
    const char *eq = strchr(payload, '=');
    if (eq && strcmp("name", payload) == 0) {
        *name = strdup(eq + 1);
        return 1;
    }
    return 0;
}

void handle_request(int client_socket) {
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        const char *api_start = strstr(buffer, "/api?payload=");
        if (api_start != NULL) {
            api_start += strlen("/api?payload=");
            char *name;
            if (parse_payload(api_start, &name)) {
                char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
                send(client_socket, response, strlen(response), 0);
                send(client_socket, name, strlen(name), 0);
                free(name);
            } else {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid payload";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}