#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *type;
} Payload;

int parse_yaml(const char *yaml, Payload *payload) {
    // Simplified YAML parsing for demonstration purposes
    const char *type_start = strstr(yaml, "type: ");
    if (type_start == NULL) return -1;
    type_start += 6; // Skip "type: "
    char *type_end = strchr(type_start, '\n');
    if (type_end == NULL) {
        payload->type = strdup(type_start);
    } else {
        int len = type_end - type_start;
        payload->type = malloc(len + 1);
        strncpy(payload->type, type_start, len);
        payload->type[len] = '\0';
    }
    return 0;
}

void handle_request(const char *query) {
    if (strstr(query, "payload=") == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter.\r\n");
        return;
    }

    const char *payload_start = strstr(query, "payload=") + 8;
    if (strstr(payload_start, "&") != NULL) {
        int len = strstr(payload_start, "&") - payload_start;
        char *encoded_payload = malloc(len + 1);
        strncpy(encoded_payload, payload_start, len);
        encoded_payload[len] = '\0';
        char *decoded_payload = malloc(strlen(encoded_payload) + 1);
        if (decoded_payload == NULL) {
            printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError: Memory allocation failed.\r\n");
            free(encoded_payload);
            return;
        }
        for (int i = 0, j = 0; encoded_payload[i]; i++, j++) {
            if (encoded_payload[i] == '%' && isxdigit(encoded_payload[i + 1]) && isxdigit(encoded_payload[i + 2])) {
                sscanf(&encoded_payload[i + 1], "%2x", &decoded_payload[j]);
                i += 2;
            } else {
                decoded_payload[j] = encoded_payload[i];
            }
        }
        decoded_payload[strlen(decoded_payload)] = '\0';
        Payload payload;
        if (parse_yaml(decoded_payload, &payload) == -1) {
            printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid YAML format.\r\n");
        } else {
            if (strcmp(payload.type, "Create") == 0) {
                printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type 'Create' is not allowed.\r\n");
            } else {
                printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully.\r\n");
            }
            free(payload.type);
        }
        free(decoded_payload);
        free(encoded_payload);
    } else {
        char *decoded_payload = strdup(payload_start);
        Payload payload;
        if (parse_yaml(decoded_payload, &payload) == -1) {
            printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid YAML format.\r\n");
        } else {
            if (strcmp(payload.type, "Create") == 0) {
                printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type 'Create' is not allowed.\r\n");
            } else {
                printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully.\r\n");
            }
            free(payload.type);
        }
        free(decoded_payload);
    }
}

int main() {
    // Simulate a request for demonstration purposes
    const char *request = "GET /?payload&type%3A+Create HTTP/1.1";
    handle_request(request);
    return 0;
}