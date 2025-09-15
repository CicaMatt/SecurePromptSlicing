#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000

void handle_request(int client_sock) {
    char buffer[4096] = {0};
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        // Check for "payload" parameter in the request
        char *payload_start = strstr(buffer, "payload=");
        if (payload_start == NULL) {
            const char *error_msg = "Error: No payload parameter found.\n";
            send(client_sock, error_msg, strlen(error_msg), 0);
            close(client_sock);
            return;
        }

        // Extract the YAML content
        payload_start += 8; // Skip past "payload="
        char *payload_end = strstr(payload_start, "\r\n");
        if (payload_end) {
            *payload_end = '\0'; // Null-terminate the YAML string
        } else {
            const char *error_msg = "Error: Invalid request format.\n";
            send(client_sock, error_msg, strlen(error_msg), 0);
            close(client_sock);
            return;
        }

        // Parse the YAML content
        yaml_parser_t parser;
        if (!yaml_parser_initialize(&parser)) {
            const char *error_msg = "YAML parsing initialization failed.\n";
            send(client_sock, error_msg, strlen(error_msg), 0);
            close(client_sock);
            return;
        }

        yaml_parser_set_input_string(&parser, payload_start, strlen(payload_start));

        yaml_event_t event;
        if (!yaml_parser_parse(&parser, &event)) {
            const char *error_msg = "Error parsing YAML.\n";
            send(client_sock, error_msg, strlen(error_msg), 0);
            yaml_parser_delete(&parser);
            close(client_sock);
            return;
        }

        // Check for type in the parsed YAML
        while (yaml_event_get_type(&event) != YAML_STREAM_END_EVENT) {
            if (yaml_event_get_type(&event) == YAML_MAPPING_START_EVENT ||
                yaml_event_get_type(&event) == YAML_SEQUENCE_START_EVENT) {
                do {
                    if (yaml_event_get_type(&event) == YAML_SCALAR_EVENT &&
                        strcmp((const char *)yaml_event_data_scalar(&event).value, "type") == 0) {
                        const char *error_msg = "Error: Type found in payload.\n";
                        send(client_sock, error_msg, strlen(error_msg), 0);
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        close(client_sock);
                        return;
                    }
                } while (yaml_parser_parse(&parser, &event));
            }
        }

        // If type is not found
        const char *success_msg = "Success: No type in payload.\n";
        send(client_sock, success_msg, strlen(success_msg), 0);

        yaml_event_delete(&event);
        yaml_parser_delete(&parser);
    } else {
        close(client_sock);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 5000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 5000
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
