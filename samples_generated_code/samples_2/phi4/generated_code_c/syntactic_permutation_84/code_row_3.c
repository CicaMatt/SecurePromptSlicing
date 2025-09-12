#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <yaml.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';

    // Check for "payload" parameter
    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_msg = "Error: No payload found.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    payload_start += 8; // Move past 'payload='
    size_t payload_len = strcspn(payload_start, "\r\n");
    char *payload_data = malloc(payload_len + 1);
    strncpy(payload_data, payload_start, payload_len);
    payload_data[payload_len] = '\0';

    // Parse YAML
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        const char *error_msg = "Error initializing YAML parser.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        free(payload_data);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, payload_data);

    yaml_event_t event;
    if (!yaml_parser_parse(&parser, &event)) {
        const char *error_msg = "Error parsing YAML.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        free(payload_data);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    while (1) {
        if (event.type == YAML_MAPPING_START_EVENT || event.type == YAML_SEQUENCE_START_EVENT) {
            do {
                if (!yaml_parser_parse(&parser, &event))
                    goto error;
            } while (!(event.type == YAML_MAPPING_END_EVENT || event.type == YAML_SEQUENCE_END_EVENT));
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            const char *error_msg = "Error: Operation type is 'Create'.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
            yaml_event_delete(&event);
            free(payload_data);
            yaml_parser_delete(&parser);
            close(client_socket);
            return;
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }

        yaml_event_delete(&event);

        if (!yaml_parser_parse(&parser, &event))
            goto error;
    }

    const char *success_msg = "Payload processed successfully.\n";
    send(client_socket, success_msg, strlen(success_msg), 0);

error:
    const char *parse_error_msg = "Error processing YAML payload.\n";
    send(client_socket, parse_error_msg, strlen(parse_error_msg), 0);
    
    yaml_event_delete(&event);
    free(payload_data);
    yaml_parser_delete(&parser);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}