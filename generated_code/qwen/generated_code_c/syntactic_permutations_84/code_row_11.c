#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

struct connection_info_struct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                  const char *url, const char *method,
                                  const char *version, const char *upload_data,
                                  size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info = cls;
    enum MHD_Result ret;
    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");

    if (!payload) {
        const char *error_response = "{\"error\": \"Missing payload parameter\"}";
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST,
                                  MHD_create_response_from_buffer(strlen(error_response), (void*)error_response, MHD_RESPMEM_PERSISTENT));
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        const char *error_response = "{\"error\": \"Failed to initialize YAML parser\"}";
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR,
                                  MHD_create_response_from_buffer(strlen(error_response), (void*)error_response, MHD_RESPMEM_PERSISTENT));
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    if (!yaml_parser_parse(&parser, &document)) {
        const char *error_response = "{\"error\": \"Failed to parse YAML\"}";
        yaml_parser_delete(&parser);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST,
                                  MHD_create_response_from_buffer(strlen(error_response), (void*)error_response, MHD_RESPMEM_PERSISTENT));
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
            yaml_node_t *key = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value = yaml_document_get_node(&document, pair->value);

            if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE) {
                if (strcmp((char *)key->data.scalar.value, "type") == 0 && strcmp((char *)value->data.scalar.value, "Create") == 0) {
                    const char *error_response = "{\"error\": \"Type Create is not allowed\"}";
                    yaml_document_delete(&document);
                    yaml_parser_delete(&parser);
                    return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST,
                                              MHD_create_response_from_buffer(strlen(error_response), (void*)error_response, MHD_RESPMEM_PERSISTENT));
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    const char *response = "{\"status\": \"success\"}";
    ret = MHD_queue_response(connection, MHD_HTTP_OK,
                              MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT));
    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}