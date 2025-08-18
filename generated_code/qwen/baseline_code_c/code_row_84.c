#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

int check_yaml_create(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *) payload, strlen(payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((const char *) event.data.scalar.value, "Create") == 0) {
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                return 1; // Create type found
            }
        }

        yaml_event_delete(&event);

    } while (!yaml_parser_check_event(&parser, YAML_STREAM_END_EVENT));

    yaml_parser_delete(&parser);
    return 0; // No Create type found
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload) {
        const char *error_message = "Error: No payload parameter provided.\n";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *) error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (check_yaml_create(payload) == 1) {
        const char *error_message = "Error: Payload type is Create.\n";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *) error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    const char *ok_message = "Payload accepted.\n";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(ok_message), (void *) ok_message, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}