#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "yaml.h"

#define PORT 5000

int start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

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
    
    printf("Server listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        int valread = read(new_socket, buffer, 1024);
        if (valread < 0) {
            perror("read");
            close(new_socket);
            continue;
        }
        
        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            const char *response = "Error: No payload parameter found\n";
            send(new_socket, response, strlen(response), 0);
        } else {
            payload_start += 8; // Move past 'payload='
            yaml_parser_t parser;
            yaml_event_t event;

            if (!yaml_parser_initialize(&parser)) {
                fprintf(stderr, "Failed to initialize YAML parser!\n");
                close(new_socket);
                continue;
            }

            yaml_parser_set_input_string(&parser, payload_start);

            while (1) {
                if (!yaml_parser_parse(&parser, &event))
                    break;

                if (event.type == YAML_STREAM_START_EVENT ||
                    event.type == YAML_DOCUMENT_START_EVENT)
                    continue;

                if (event.type == YAML_MAPPING_START_EVENT || 
                    event.type == YAML_SEQUENCE_START_EVENT)
                    continue;

                if (event.type == YAML_SCALAR_EVENT) {
                    if (!strcmp((char *)event.data.scalar.value, "Create")) {
                        const char *response = "Error: Payload contains 'Create'\n";
                        send(new_socket, response, strlen(response), 0);
                        yaml_event_delete(&event);
                        break;
                    }
                }

                yaml_event_delete(&event);
            }

            if (yaml_parser_finalize(&parser))
                fprintf(stderr, "Failed to finalize YAML parser!\n");

            const char *response = "Request processed successfully\n";
            send(new_socket, response, strlen(response), 0);
        }

        close(new_socket);
    }
    
    close(server_fd);
    return 0;
}

int main() {
    start_server();
    return 0;
}