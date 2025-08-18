#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    
    if (valread > 0) {
        printf("Received: %s\n", buffer);
        
        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            const char *error_msg = "Error: No payload parameter found.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            payload_start += 8; // Move past 'payload='
            
            yaml_parser_t parser;
            FILE *input_file = fmemopen(payload_start, strlen(payload_start), "r");
            if (!input_file) {
                const char *error_msg = "Error: Failed to open file from memory.\n";
                send(client_socket, error_msg, strlen(error_msg), 0);
                return;
            }
            
            yaml_parser_initialize(&parser);
            yaml_parser_set_input_file(&parser, input_file);

            yaml_event_t event;
            int done = 0;

            while (!done) {
                if (!yaml_parser_parse(&parser, &event)) {
                    fprintf(stderr, "Parser error %d\n", parser.error);
                    break;
                }

                switch (event.type) {
                    case YAML_STREAM_START_EVENT:
                        break;
                    case YAML_DOCUMENT_START_EVENT:
                        break;
                    case YAML_MAPPING_START_EVENT:
                        break;
                    case YAML_SEQUENCE_START_EVENT:
                        break;
                    case YAML_SCALAR_EVENT: {
                        if (!strcmp((char*)event.data.scalar.value, "Create")) {
                            const char *error_msg = "Error: Type 'Create' is not allowed.\n";
                            send(client_socket, error_msg, strlen(error_msg), 0);
                            done = 1;
                        }
                        break;
                    }
                    default:
                        break;
                }

                yaml_event_delete(&event);

                if (parser.error != YAML_NO_ERROR) {
                    done = 1;
                }
            }

            yaml_parser_delete(&parser);
            fclose(input_file);

            if (!done) {
                const char *success_msg = "Success: Payload processed.\n";
                send(client_socket, success_msg, strlen(success_msg), 0);
            }
        }
    }

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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        printf("Connection accepted\n");

        if (fork() == 0) {
            close(server_fd);
            handle_client(new_socket);
            exit(0);
        }
        
        close(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}