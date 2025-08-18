#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }

    char *payload_param = strstr(buffer, "payload=");
    if (!payload_param) {
        const char *error_msg = "Error: 'payload' parameter is missing.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
    } else {
        payload_param += strlen("payload=");

        yaml_parser_t parser;
        FILE *input_file = fmemopen((void *)payload_param, strlen(payload_param), "r");
        if (!input_file) {
            const char *error_msg = "Error: Unable to parse payload.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            yaml_parser_initialize(&parser);
            yaml_parser_set_input_file(&parser, input_file);

            yaml_event_t event;
            if (!yaml_parser_parse(&parser, &event)) {
                const char *error_msg = "Error: Unable to parse YAML.\n";
                send(client_socket, error_msg, strlen(error_msg), 0);
                fclose(input_file);
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                close(client_socket);
                return;
            }

            if (event.type == YAML_SCALAR_EVENT && strcmp(event.data.scalar.value, "Create") == 0) {
                const char *error_msg = "Error: 'type' is 'Create'.\n";
                send(client_socket, error_msg, strlen(error_msg), 0);
            } else {
                const char *success_msg = "Success: Payload processed.\n";
                send(client_socket, success_msg, strlen(success_msg), 0);
            }

            yaml_event_delete(&event);
        }
    }

    fclose(input_file);
    close(client_socket);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t addr_len = sizeof(client_address);

        if ((client_socket = accept(server_fd, (struct sockaddr *)&client_address, &addr_len)) < 0) {
            perror("accept");
            continue;
        }

        handle_request(client_socket);
    }

    return 0;
}