#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload) {
        const char *response = "{\"error\": \"Missing payload parameter\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char *) payload, strlen(payload));

    yaml_event_t event;
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event))
            break;

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *) event.data.scalar.value, "type") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event))
                        goto cleanup;

                    if (event.type == YAML_SCALAR_EVENT && strcmp((const char *) event.data.scalar.value, "Create") == 0) {
                        const char *response = "{\"error\": \"Type Create is not allowed\"}";
                        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
                        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
                        MHD_destroy_response(mhd_response);
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return ret;
                    }
                }
                break;
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

cleanup:
    yaml_parser_delete(&parser);

    const char *response = "{\"status\": \"success\"}";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}