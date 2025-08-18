#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[4096] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    if (valread > 0) {
        char *payload_start = strstr(buffer, "payload=");
        if (payload_start) {
            payload_start += strlen("payload=");

            // Parse YAML
            yaml_parser_t parser;
            yaml_event_t event;

            FILE *file = fmemopen(payload_start, valread - (payload_start - buffer), "r");
            if (!file) {
                send(client_socket, "Error: Failed to open memory file\n", 39, 0);
                return;
            }

            yaml_parser_initialize(&parser);
            yaml_parser_set_input_file(&parser, file);

            while (1) {
                if (!yaml_parser_parse(&parser, &event)) {
                    fprintf(stderr, "Parser error %d\n", parser.error);
                    break;
                }
                if (event.type == YAML_STREAM_END_EVENT) break;

                // Check for 'type: Create'
                if (event.type == YAML_SCALAR_EVENT && strcmp(event.data.scalar.value, "Create") == 0) {
                    send(client_socket, "Error: Type is Create\n", 24, 0);
                    yaml_event_delete(&event);
                    break;
                }

                yaml_event_delete(&event);
            }
            yaml_parser_delete(&parser);
            fclose(file);

            if (send(client_socket, "Success\n", 8, 0) < 0) {
                perror("Send error");
            }
        } else {
            send(client_socket, "Error: No payload parameter\n", 31, 0);
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("Accept");
            continue;
        }
        handle_client(new_socket);
        close(new_socket);
    }

    if (new_socket < 0) {
        perror("Accept failed");
    }

    close(server_fd);
    return 0;
}