#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

char *handle_request(const char *request) {
    const char *payload_start = strstr(request, "payload=");
    if (!payload_start) {
        return strdup("Error: No payload parameter found.");
    }

    payload_start += strlen("payload=");
    char payload[BUFFER_SIZE];
    strncpy(payload, payload_start, BUFFER_SIZE);
    char *end_of_payload = strchr(payload, ' ');
    if (end_of_payload) {
        *end_of_payload = '\0';
    }

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return strdup("Error: Failed to initialize YAML parser.");
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    int done = 0;
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return strdup("Error: Failed to parse YAML.");
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                    done = 1;
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return strdup("Error: Payload type is Create.");
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return strdup("Payload processed successfully.");
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        read(new_socket, buffer, BUFFER_SIZE);
        char *response = handle_request(buffer);
        send(new_socket, response, strlen(response), 0);
        free(response);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}