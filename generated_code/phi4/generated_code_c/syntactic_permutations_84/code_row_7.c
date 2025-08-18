#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *type;
} Payload;

int parse_yaml_payload(const char *payload, Payload *parsed_payload) {
    // Simulated parsing logic for illustration purposes
    if (strstr(payload, "type: Create") != NULL) {
        parsed_payload->type = strdup("Create");
        return 1; // Successfully parsed as a 'Create' type
    }
    return 0;
}

void handle_request(const char *payload) {
    Payload parsed_payload;

    if (!parse_yaml_payload(payload, &parsed_payload)) {
        printf("Error: Invalid YAML payload\n");
        return;
    }

    if (strcmp(parsed_payload.type, "Create") == 0) {
        printf("Error: 'Create' operation is not allowed\n");
        free(parsed_payload.type);
        return;
    }

    printf("Request processed successfully\n");
    free(parsed_payload.type);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <payload>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *payload = argv[1];
    handle_request(payload);

    return EXIT_SUCCESS;
}