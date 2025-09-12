#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} Header;

typedef struct {
    int type; // 1 for Create, other types can be added as needed
} Payload;

int parse_payload(const char *payload_str, Payload *payload) {
    if (sscanf(payload_str, "type=%d", &payload->type) != 1) {
        return -1;
    }
    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';

    Header headers[10]; // Assuming a maximum of 10 headers
    int header_count = 0;

    char *line = strtok(buffer, "\r\n");
    while (line != NULL) {
        if (header_count == 0 && strncmp(line, "GET", 3) == 0) {
            line = strtok(NULL, " ");
            char *query_str = strchr(line, '?');
            if (!query_str) {
                send(client_socket, "Error: No payload parameter\n", 30, 0);
                close(client_socket);
                return;
            }
            query_str++;
        } else if (header_count > 0 && header_count < 10) {
            char *key = strtok(line, ": ");
            if (key != NULL) {
                headers[header_count - 1].key = strdup(key);
                char *value = strtok(NULL, "\r\n");
                if (value != NULL) {
                    headers[header_count - 1].value = strdup(value);
                }
                header_count++;
            }
        } else {
            break;
        }
        line = strtok(NULL, "\r\n");
    }

    for (int i = 0; i < header_count; i++) {
        if (strcmp(headers[i].key, "payload") == 0) {
            Payload payload;
            if (parse_payload(headers[i].value, &payload) != 0 || payload.type == 1) {
                send(client_socket, "Error: Invalid or Create type payload\n", 40, 0);
            } else {
                send(client_socket, "Payload received successfully\n", 30, 0);
            }
            break;
        }
    }

    for (int i = 0; i < header_count; i++) {
        free(headers[i].key);
        free(headers[i].value);
    }
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
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
    address.sin_port = htons(PORT);

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

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_request(client_socket);
    }

    close(server_fd);
    return 0;
}