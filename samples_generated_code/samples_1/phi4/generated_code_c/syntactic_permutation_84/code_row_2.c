#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <yaml.h>

void handle_request(int client_sock) {
    char buffer[4096];
    int bytes_read = read(client_sock, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) return;

    buffer[bytes_read] = '\0';
    
    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_msg = "Error: Missing payload parameter.\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        return;
    }
    payload_start += strlen("payload=");

    char *payload_end = strchr(payload_start, '&');
    if (payload_end) {
        *payload_end = '\0';
    }

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        const char *error_msg = "Error: Cannot initialize YAML parser.\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        close(client_sock);
        return;
    }

    FILE *stream = fmemopen(payload_start, payload_end - payload_start, "r");
    if (!stream) {
        const char *error_msg = "Error: Cannot open memory stream.\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        yaml_parser_delete(&parser);
        close(client_sock);
        return;
    }

    yaml_parser_set_input_file(&parser, stream);

    if (!yaml_parser_parse(&parser, &event)) {
        const char *error_msg = "Error: Cannot parse YAML.\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        yaml_event_delete(&event);
        fclose(stream);
        yaml_parser_delete(&parser);
        close(client_sock);
        return;
    }

    if (event.type != YAML_MAPPING_START_EVENT && event.type != YAML_SEQUENCE_START_EVENT) {
        const char *error_msg = "Error: Invalid YAML format.\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        yaml_event_delete(&event);
        fclose(stream);
        yaml_parser_delete(&parser);
        close(client_sock);
        return;
    }

    int type_found = 0;
    while (yaml_parser_parse(&parser, &event)) {
        if (type_found) break;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) break;
            
            if (event.type != YAML_SCALAR_EVENT) {
                const char *error_msg = "Error: Invalid type field in YAML.\n";
                send(client_sock, error_msg, strlen(error_msg), 0);
                yaml_event_delete(&event);
                fclose(stream);
                yaml_parser_delete(&parser);
                close(client_sock);
                return;
            }

            if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                const char *error_msg = "Error: Invalid type 'Create'.\n";
                send(client_sock, error_msg, strlen(error_msg), 0);
                yaml_event_delete(&event);
                fclose(stream);
                yaml_parser_delete(&parser);
                close(client_sock);
                return;
            }
        }

        yaml_event_delete(&event);
    }

    const char *success_msg = "Request processed successfully.\n";
    send(client_sock, success_msg, strlen(success_msg), 0);

    yaml_event_delete(&event);
    fclose(stream);
    yaml_parser_delete(&parser);
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
    address.sin_port = htons(5000);

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
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}