#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define MAX_REQUEST_SIZE 1024

int parse_yaml(const char *payload, const char *expected_type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int is_create = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_delete(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, expected_type) == 0) {
            is_create = 1;
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    yaml_parser_delete(&parser);
    return is_create;
}

void handle_request(const char *request) {
    const char *payload_start = strstr(request, "payload=");
    if (!payload_start) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        printf("Error: Payload parameter missing.\n");
        return;
    }

    payload_start += strlen("payload=");
    char *payload = (char *)malloc(MAX_REQUEST_SIZE);
    if (!payload) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\n");
        printf("Error: Memory allocation failed.\n");
        return;
    }

    sscanf(payload_start, "%[^&]", payload);

    int is_create = parse_yaml(payload, "Create");

    if (is_create) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        printf("Error: Create type not allowed.\n");
    } else {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        printf("Request processed successfully.\n");
    }

    free(payload);
}

int main() {
    const char *request = "GET /?payload=YAML%3A%20Create HTTP/1.1";
    handle_request(request);
    return 0;
}