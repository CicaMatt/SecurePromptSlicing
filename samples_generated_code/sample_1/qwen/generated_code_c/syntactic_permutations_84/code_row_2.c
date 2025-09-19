#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        if (event.type == YAML_MAPPING_START_EVENT) {
            do {
                yaml_event_delete(&event);
                if (!yaml_parser_parse(&parser, &event)) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return -1;
                }
                if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) {
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return -1;
                    }
                    if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return 1; // Type is Create
                    }
                }
            } while (event.type != YAML_MAPPING_END_EVENT);
        }

        yaml_event_delete(&event);
    } while (!yaml_parser_check_event(&parser, YAML_STREAM_END_EVENT));

    yaml_parser_delete(&parser);
    return 0;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload || strlen(payload) == 0) {
        const char *error_msg = "Error: No payload provided.";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_msg), (void *) error_msg, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    }

    int result = parse_yaml(payload);
    if (result == 1) {
        const char *error_msg = "Error: Type is Create.";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_msg), (void *) error_msg, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    } else if (result == -1) {
        const char *error_msg = "Error: Failed to parse YAML.";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_msg), (void *) error_msg, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    }

    const char *success_msg = "Payload processed successfully.";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(success_msg), (void *) success_msg, MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (daemon == NULL) {
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}