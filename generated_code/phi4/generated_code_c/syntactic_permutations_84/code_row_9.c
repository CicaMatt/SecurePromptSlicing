#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

void handle_request(const char *query) {
    const char *error_msg = "Error: No payload parameter found.\n";
    const char *create_error_msg = "Error: Payload type is Create.\n";

    // Find the position of 'payload=' in the query string
    const char *payload_pos = strstr(query, "payload=");
    if (!payload_pos) {
        printf("%s", error_msg);
        return;
    }

    // Move past 'payload=' to get the payload value
    payload_pos += strlen("payload=");

    // Create a YAML parser context
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser!\n");
        exit(EXIT_FAILURE);
    }

    // Set input string for the parser
    yaml_parser_set_input_string(&parser, payload_pos);

    // Create a YAML event and parse it
    yaml_event_t event;
    if (!yaml_parser_parse(&parser, &event)) {
        fprintf(stderr, "Failed to parse YAML!\n");
        yaml_parser_delete(&parser);
        exit(EXIT_FAILURE);
    }

    // Check the type of the first event
    if (event.type == YAML_STREAM_START_EVENT) {
        // Get the next event which should be a document start
        yaml_parser_parse(&parser, &event);

        // Check for mapping start to get key-value pairs
        while (event.type != YAML_DOCUMENT_END_EVENT && event.type != YAML_STREAM_END_EVENT) {
            if (event.type == YAML_MAPPING_START_EVENT || event.type == YAML_SEQUENCE_START_EVENT) {
                yaml_parser_parse(&parser, &event);
                if (event.type == YAML_SCALAR_EVENT) {
                    // Check for 'type' key
                    const char *key = (const char *)yaml_event_get_data(&event);
                    if (strcmp(key, "type") == 0) {
                        // Get the next event which should be a scalar value
                        yaml_parser_parse(&parser, &event);
                        if (event.type == YAML_SCALAR_EVENT) {
                            const char *value = (const char *)yaml_event_get_data(&event);

                            // Check if type is 'Create'
                            if (strcmp(value, "Create") == 0) {
                                printf("%s", create_error_msg);
                            }
                        }
                    }
                }
            }

            yaml_parser_parse(&parser, &event);
        }
    }

    // Cleanup
    yaml_event_delete(&event);
    yaml_parser_delete(&parser);
}

int main() {
    const char *query = "GET /?payload=%7B%22type%22%3A+%22Create%22%7D HTTP/1.1";

    handle_request(query);

    return 0;
}
