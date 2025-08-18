#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

int handle_request(char *request) {
    char *param = strstr(request, "action=");
    if (param == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Missing 'action' parameter.\n");
        return -1;
    }

    param += strlen("action=");
    if (param[0] == '"') {
        param++;
        char *end = strchr(param, '"');
        if (end) {
            *end = '\0';
        }
    }

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    const char *input = param;
    yaml_parser_set_input_string(&parser, (const unsigned char *)input, strlen(input));

    int create_type_found = 0;
    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            create_type_found = 1;
            break;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    if (create_type_found) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: 'Create' type is not allowed.\n");
        return -1;
    }

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("Request processed successfully.\n");

    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread > 0) {
            handle_request(buffer);
        }
        close(new_socket);
    }

    return 0;
}