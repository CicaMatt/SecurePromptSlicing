#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *input, const char *type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *) input, strlen(input));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto end;
        }

        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *) event.data.scalar.value, "type")) {
            found_type = 1;
        } else if (event.type == YAML_SCALAR_EVENT && found_type) {
            if (!strcmp((char *) event.data.scalar.value, type)) {
                yaml_event_delete(&event);
                goto end;
            }
            found_type = 0;
        }

        yaml_event_delete(&event);
    }

end:
    yaml_parser_delete(&parser);
    return -1;
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    read(client_socket, buffer, BUFFER_SIZE);

    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 27\r\n\r\nPayload parameter is missing.\r\n", 86);
        return -1;
    }

    payload_start += strlen("payload=");
    char *payload_end = strchr(payload_start, '&');
    if (payload_end) {
        *payload_end = '\0';
    }

    int is_create = parse_yaml(payload_start, "Create");
    if (is_create == 0) {
        write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\n\r\nType 'Create' is not allowed.\r\n", 83);
        return -1;
    }

    write(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 17\r\n\r\nRequest processed successfully.\r\n", 69);
    return 0;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
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
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        handle_request(client_fd);
        close(client_fd);
    }

    return 0;
}