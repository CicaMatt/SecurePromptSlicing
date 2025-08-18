#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *input, const char **type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    *type = NULL;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (unsigned char *)input, strlen(input));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) goto error;

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (*type == NULL && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                    *type = "Create";
                }
                break;
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0;

error:
    yaml_parser_delete(&parser);
    return -1;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);

    if (bytes_read > 0) {
        const char *payload_start = strstr(buffer, "payload=");
        if (payload_start == NULL) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 26\r\n\r\nPayload parameter not found.";
            write(client_socket, response, strlen(response));
        } else {
            payload_start += strlen("payload=");
            size_t payload_len = strcspn(payload_start, "&\r\n");
            char *decoded_payload = malloc(payload_len + 1);
            if (decoded_payload) {
                memset(decoded_payload, 0, payload_len + 1);
                strncpy(decoded_payload, payload_start, payload_len);

                const char *type;
                if (parse_yaml(decoded_payload, &type) == 0 && type != NULL && strcmp(type, "Create") == 0) {
                    const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\n\r\nType 'Create' is not allowed.";
                    write(client_socket, response, strlen(response));
                } else {
                    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nOK";
                    write(client_socket, response, strlen(response));
                }

                free(decoded_payload);
            }
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;

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
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, NULL, NULL);
        handle_request(new_socket);
    }

    return 0;
}