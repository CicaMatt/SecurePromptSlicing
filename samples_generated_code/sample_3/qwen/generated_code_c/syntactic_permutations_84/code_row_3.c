#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

static int handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload)
        return MHD_NO;

    yaml_parser_t parser;
    yaml_document_t document;
    yaml_node_t *node;
    int type_is_create = 0;

    if (!yaml_parser_initialize(&parser))
        return MHD_NO;

    yaml_parser_set_input_string(&parser, (unsigned char*) payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        return MHD_NO;
    }

    node = yaml_document_get_root_node(&document);

    if (node->type == YAML_MAPPING_NODE) {
        yaml_node_pair_t *pair;
        for (size_t i = 0; i < node->data.mapping.pairs.size; i++) {
            pair = yaml_document_get_pairs(document, node)[i];
            if (yaml_document_get_scalar_value(document, yaml_document_get_node(document, pair->key)) == "type") {
                const char *value = yaml_document_get_scalar_value(document, yaml_document_get_node(document, pair->value));
                if (strcmp(value, "Create") == 0)
                    type_is_create = 1;
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    if (!type_is_create) {
        const char *response = "OK";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    } else {
        const char *response = "Error: Type is Create";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}