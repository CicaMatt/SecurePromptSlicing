#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

const char *error_response = "{\"error\": \"Invalid request\"}";
const char *type_error_response = "{\"error\": \"Type Create is not allowed\"}";

int check_payload(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return 0;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    int done = 0;
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return 1;
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

        done = (event.type == YAML_STREAM_END_EVENT);
    }

    yaml_parser_delete(&parser);
    return 0;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    struct MHD_Response *response;
    int ret;

    const char *payload = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "payload");
    if (!payload) {
        response = MHD_create_response_from_buffer(strlen(error_response), (void *)error_response, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (check_payload(payload)) {
        response = MHD_create_response_from_buffer(strlen(type_error_response), (void *)type_error_response, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    const char *success_response = "{\"status\": \"success\"}";
    response = MHD_create_response_from_buffer(strlen(success_response), (void *)success_response, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}