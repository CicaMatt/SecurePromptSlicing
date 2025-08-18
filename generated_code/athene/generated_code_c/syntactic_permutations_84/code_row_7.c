#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

int parse_yaml(const char *payload, const char *expected_type) {
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

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "type") == 0 && found_type == 0) {
                    found_type = 1;
                } else if (found_type == 1) {
                    char *value = malloc(event.data.scalar.length + 1);
                    strncpy(value, (char *)event.data.scalar.value, event.data.scalar.length);
                    value[event.data.scalar.length] = '\0';
                    int result = strcmp(value, expected_type) == 0 ? 0 : -1;
                    free(value);
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return result;
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return -1;
}

int main() {
    char *query = getenv("QUERY_STRING");
    if (query == NULL) {
        printf("Content-Type: text/plain\r\n\r\nError: Missing payload parameter.\r\n");
        return 1;
    }

    const char *payload_start = strstr(query, "payload=");
    if (payload_start == NULL || payload_start == query) {
        printf("Content-Type: text/plain\r\n\r\nError: Missing payload parameter.\r\n");
        return 1;
    }

    payload_start += 8; // Skip "payload="

    int is_create = parse_yaml(payload_start, "Create");

    if (is_create == 0) {
        printf("Content-Type: text/plain\r\n\r\nError: Type 'Create' not allowed.\r\n");
        return 1;
    }

    printf("Content-Type: text/plain\r\n\r\nOK\r\n");
    return 0;
}