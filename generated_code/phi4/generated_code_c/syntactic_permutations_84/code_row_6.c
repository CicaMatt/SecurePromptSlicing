#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <yaml.h>

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[4096];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    printf("Received: %s\n", buffer);

    // Check for 'payload' parameter
    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_msg = "Error: No payload parameter found.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    // Extract the YAML payload
    payload_start += strlen("payload="); // Move to the start of the YAML content
    yaml_parser_t parser;
    FILE *yaml_file = fmemopen(payload_start, bytes_received - (payload_start - buffer), "r");
    
    if (!yaml_file) {
        const char *error_msg = "Error: Failed to parse payload.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, yaml_file);

    yaml_event_t event;
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            const char *error_msg = "Error: Failed to parse YAML.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            fclose(yaml_file);
            close(client_socket);
            return;
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            done = 1;
        } else if (event.type == YAML_MAPPING_START_EVENT) {
            yaml_event_t key_event, value_event;

            // Check the type
            if (!yaml_parser_parse(&parser, &key_event)) goto error;
            if (!yaml_parser_parse(&parser, &value_event)) goto error;

            if (strcmp((char*)key_event.data.scalar.value, "type") == 0) {
                if (strcmp((char*)value_event.data.scalar.value, "Create") == 0) {
                    const char *error_msg = "Error: Type is 'Create'.\n";
                    send(client_socket, error_msg, strlen(error_msg), 0);
                    yaml_event_delete(&key_event);
                    yaml_event_delete(&value_event);
                    yaml_parser_delete(&parser);
                    fclose(yaml_file);
                    close(client_socket);
                    return;
                }
            }

            yaml_event_delete(&key_event);
            yaml_event_delete(&value_event);
        }

        yaml_event_delete(&event);
    }

    const char *success_msg = "Success: Payload processed.\n";
    send(client_socket, success_msg, strlen(success_msg), 0);

error:
    yaml_parser_delete(&parser);
    fclose(yaml_file);
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
        printf("Waiting for connections...\n");

        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}