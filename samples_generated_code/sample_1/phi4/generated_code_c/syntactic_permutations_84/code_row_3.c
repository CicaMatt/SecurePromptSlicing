#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "yaml.h"

#define PORT 5000

void handle_request(int client_socket) {
    char buffer[4096];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        
        char *payload_str = strstr(buffer, "payload=");
        if (payload_str) {
            payload_str += strlen("payload="); // Move to the start of the actual payload

            yaml_parser_t parser;
            FILE *input_file = fmemopen(payload_str, bytes_received - (payload_str - buffer), "r");
            
            yaml_parser_initialize(&parser);
            yaml_parser_set_input_file(&parser, input_file);

            yaml_event_t event;
            int done = 0;

            while (!done) {
                if (!yaml_parser_parse(&parser, &event)) {
                    fprintf(stderr, "Parser error %d\n", parser.error);
                    break;
                }

                if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "Create")) {
                    const char *response = "Error: 'Create' type is not allowed.\n";
                    send(client_socket, response, strlen(response), 0);
                }

                yaml_event_delete(&event);

                if (event.type == YAML_STREAM_END_EVENT) {
                    done = 1;
                }
            }

            fclose(input_file);
            yaml_parser_delete(&parser);
        } else {
            const char *response = "No payload found.\n";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
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

    while ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        handle_request(client_socket);
    }

    close(server_fd);
    return 0;
}
