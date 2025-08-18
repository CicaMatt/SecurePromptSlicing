#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000

void handle_connection(int client_sock) {
    char buffer[1024] = {0};
    int valread = read(client_sock, buffer, sizeof(buffer));
    
    if (valread > 0) {
        printf("Received: %s\n", buffer);

        // Check for the presence of the parameter 'type'
        char *param_pos = strstr(buffer, "type=");
        if (!param_pos) {
            const char *error_msg = "Error: Missing 'type' parameter.\n";
            send(client_sock, error_msg, strlen(error_msg), 0);
        } else {
            // Parse YAML and check type
            yaml_parser_t parser;
            FILE *file = fmemopen(param_pos + 5, valread - (param_pos - buffer) - 5, "r");
            if (!yaml_parser_initialize(&parser)) {
                fprintf(stderr, "Failed to initialize YAML parser!\n");
                close(client_sock);
                return;
            }
            
            yaml_parser_set_input_file(&parser, file);

            yaml_event_t event;
            if (!yaml_parser_parse(&parser, &event)) {
                fprintf(stderr, "Error parsing YAML!\n");
                yaml_parser_delete(&parser);
                fclose(file);
                close(client_sock);
                return;
            }

            if (event.type == YAML_SCALAR_EVENT && strcmp(event.data.scalar.value, "Create") == 0) {
                const char *error_msg = "Error: Type is 'Create'.\n";
                send(client_sock, error_msg, strlen(error_msg), 0);
            } else {
                const char *success_msg = "Success: Valid request.\n";
                send(client_sock, success_msg, strlen(success_msg), 0);
            }

            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            fclose(file);
        }
    }
    
    close(client_sock);
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_connection(new_socket);
    }

    return 0;
}