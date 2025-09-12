#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received <= 0) return;

    const char *payload_param = "payload=";
    char *payload_start = strstr(buffer, payload_param);
    
    if (!payload_start) {
        const char *error_msg = "Error: Payload parameter missing.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
    } else {
        payload_start += strlen(payload_param); // Move past the 'payload=' part
        yaml_parser_t parser;
        if (!yaml_parser_initialize(&parser)) {
            perror("Failed to initialize YAML parser");
            const char *error_msg = "Error: Failed to parse YAML.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
            return;
        }

        yaml_token_t token;
        FILE *input = fmemopen(payload_start, bytes_received - (payload_start - buffer), "r");
        yaml_parser_set_input_file(&parser, input);

        if (!yaml_parser_scan(&parser, &token)) {
            const char *error_msg = "Error: Failed to scan YAML.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
            yaml_parser_delete(&parser);
            fclose(input);
            return;
        }

        if (strcmp((char *)token.data.scalar.value, "Create") == 0) {
            const char *error_msg = "Error: Type 'Create' is not allowed.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            const char *success_msg = "Payload received and processed successfully.\n";
            send(client_socket, success_msg, strlen(success_msg), 0);
        }

        yaml_token_delete(&token);
        yaml_parser_delete(&parser);
        fclose(input);
    }
}

int main() {
    int server_fd, new_socket;
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        handle_request(new_socket);
        close(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    close(server_fd);
    return 0;
}