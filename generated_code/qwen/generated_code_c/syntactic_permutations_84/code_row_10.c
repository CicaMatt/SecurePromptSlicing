#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 8888

const char *error_message = "Error: payload parameter not found or type is Create\n";

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (payload == NULL) {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message),
                                                                        (void *) error_message,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        return MHD_NO;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *) payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message),
                                                                        (void *) error_message,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root->type == YAML_MAPPING_NODE) {
        for (size_t i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
            yaml_node_t *keyNode = yaml_document_get_node(&document, pair.key);
            if (strcmp((const char *) keyNode->data.scalar.value, "type") == 0) {
                yaml_node_t *valueNode = yaml_document_get_node(&document, pair.value);
                if (strcmp((const char *) valueNode->data.scalar.value, "Create") == 0) {
                    yaml_parser_delete(&parser);
                    yaml_document_delete(&document);

                    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message),
                                                                                (void *) error_message,
                                                                                MHD_RESPMEM_PERSISTENT);
                    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
                    MHD_destroy_response(response);
                    return ret;
                }
            }
        }
    }

    yaml_parser_delete(&parser);
    yaml_document_delete(&document);

    const char *response_message = "Success\n";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_message),
                                                                    (void *) response_message,
                                                                    MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}