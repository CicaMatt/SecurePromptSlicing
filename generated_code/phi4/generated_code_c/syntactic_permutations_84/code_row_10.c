#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    const char *payload_start = strstr(request, "payload=");
    if (payload_start == NULL) {
        printf("Error: No payload parameter found.\n");
        return;
    }

    payload_start += strlen("payload=");

    // Extract the payload
    char *payload_end = strchr(payload_start, '&');
    size_t payload_length = (payload_end != NULL) ? (size_t)(payload_end - payload_start) : strlen(payload_start);
    char *payload = strndup(payload_start, payload_length);

    if (payload == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Check if the type is "Create"
    const char *type_start = strstr(payload, "type:");
    if (type_start != NULL) {
        type_start += strlen("type:");

        char *type_end = strchr(type_start, '\n');
        size_t type_length = (type_end != NULL) ? (size_t)(type_end - type_start) : strlen(type_start);
        char *type = strndup(type_start, type_length);

        if (strcmp(type, "Create") == 0) {
            printf("Error: Payload type is Create.\n");
        } else {
            printf("Payload processed successfully.\n");
        }

        free(type);
    } else {
        printf("Error: No type found in payload.\n");
    }

    free(payload);
}

int main() {
    char buffer[BUFFER_SIZE];

    // Simulate a web request
    printf("Enter the request URL:\n");
    fgets(buffer, BUFFER_SIZE, stdin);

    handle_request(buffer);

    return 0;
}