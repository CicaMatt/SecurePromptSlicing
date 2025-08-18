#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

const char *error_message = "{\"error\": \"Invalid request\"}";
const char *create_error_message = "{\"error\": \"Create type not allowed\"}";

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload) {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload), NULL);

    yaml_event_t event;
    if (!yaml_parser_parse(&parser, &event)) {
        yaml_parser_delete(&parser);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (event.type != YAML_DOCUMENT_START_EVENT) {
        yaml_parser_delete(&parser);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }
    yaml_event_delete(&event);

    if (!yaml_parser_parse(&parser, &event)) {
        yaml_parser_delete(&parser);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (event.type != YAML_MAPPING_START_EVENT) {
        yaml_parser_delete(&parser);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void *)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }
    yaml_event_delete(&event);

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) {
                break;
            }
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                yaml_parser_delete(&parser);
                struct MHD_Response *response = MHD_create_response_from_buffer(strlen(create_error_message), (void *)create_error_message, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
                MHD_destroy_response(response);
                return ret;
            }
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}