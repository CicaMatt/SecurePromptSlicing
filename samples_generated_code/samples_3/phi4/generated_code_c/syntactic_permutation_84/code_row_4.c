#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_client(int client_fd);
int parse_yaml_payload(const char *payload, int expected_type);
void send_response(int client_fd, const char *response);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            close(new_socket);
            continue;
        }
        
        handle_client(new_socket);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_fd, buffer, BUFFER_SIZE - 1);

    if (valread < 0) {
        perror("read");
        send_response(client_fd, "Error reading request\n");
        return;
    }

    printf("%s", buffer);
    
    char *payload_param = strstr(buffer, "payload=");
    if (!payload_param) {
        send_response(client_fd, "Error: Missing payload parameter\n");
        return;
    }
    
    // Extract the payload value
    payload_param += strlen("payload=");

    const yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        send_response(client_fd, "Error initializing YAML parser\n");
        return;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload_param, strlen(payload_param));

    while (1) {
        if (!yaml_parser_parse(&parser, &event))
            break;

        if (event.type == YAML_STREAM_END_EVENT)
            break;

        if (event.type == YAML_MAPPING_START_EVENT || event.type == YAML_SEQUENCE_START_EVENT) {
            // Check for 'type' key
            yaml_event_delete(&event);
            while (1) {
                if (!yaml_parser_parse(&parser, &event))
                    break;

                if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
                    yaml_event_delete(&event);

                    if (!yaml_parser_parse(&parser, &event)) 
                        break;
                    
                    if (event.type != YAML_SCALAR_EVENT)
                        break;

                    int result = parse_yaml_payload(event.data.scalar.value, 1);
                    if (result < 0) {
                        send_response(client_fd, "Error: Payload type is Create\n");
                    } else {
                        send_response(client_fd, "Payload processed successfully\n");
                    }
                    
                    yaml_event_delete(&event);
                    break;
                }

                yaml_event_delete(&event);
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
}

int parse_yaml_payload(const char *value, int expected_type) {
    if (strcmp(value, "Create") == 0 && expected_type == 1)
        return -1;
    
    return 0;
}

void send_response(int client_fd, const char *response) {
    write(client_fd, response, strlen(response));
}