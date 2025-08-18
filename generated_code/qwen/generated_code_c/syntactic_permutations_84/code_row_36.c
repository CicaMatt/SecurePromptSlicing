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

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        if (event.type == YAML_MAPPING_START_EVENT) {
            continue;
        } else if (event.type == YAML_SCALAR_EVENT) {
            const char *key = (const char *)event.data.scalar.value;
            yaml_event_delete(&event);

            if (!yaml_parser_parse(&parser, &event)) {
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                return -1;
            }

            if (strcmp(key, "type") == 0 && strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                return 1; // Type is Create
            }

            yaml_event_delete(&event);
        }
    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload) {
        const char *response = "{\"error\": \"Missing payload parameter\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    if (parse_yaml(payload) == 1) {
        const char *response = "{\"error\": \"Type cannot be Create\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    const char *response = "{\"message\": \"Success\"}";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
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