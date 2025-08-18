#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define MAX_PAYLOAD_SIZE 1024

void send_response(const char *message) {
    printf("Content-Type: text/plain\n\n");
    printf("%s\n", message);
}

int parse_yaml(const char *payload, const char *type_to_check) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        if (event.type == YAML_SCALAR_EVENT && !found_type) {
            const char *key = (char *)event.data.scalar.value;
            yaml_event_delete(&event);

            if (!yaml_parser_parse(&parser, &event)) {
                break;
            }

            if (event.type == YAML_SCALAR_EVENT) {
                const char *value = (char *)event.data.scalar.value;
                if (strcmp(key, "type") == 0 && strcmp(value, type_to_check) == 0) {
                    found_type = 1;
                }
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return found_type;
}

int main() {
    char *query_string = getenv("QUERY_STRING");
    if (!query_string || strstr(query_string, "payload=") == NULL) {
        send_response("Error: Missing payload parameter.");
        return 1;
    }

    char *payload_start = strchr(query_string, '=') + 1;
    char payload[MAX_PAYLOAD_SIZE];
    sscanf(payload_start, "%1023s", payload);

    if (parse_yaml(payload, "Create")) {
        send_response("Error: Type 'Create' is not allowed.");
        return 1;
    }

    send_response("Payload processed successfully.");
    return 0;
}