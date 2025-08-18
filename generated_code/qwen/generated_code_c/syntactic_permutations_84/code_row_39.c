#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include "yaml.h"

#define PORT 5000

static int handle_request(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload)
        return MHD_YES;

    yaml_parser_t parser;
    yaml_document_t document;
    int done_parsing = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        return MHD_NO;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        fprintf(stderr, "Parser load failed\n");
        yaml_parser_delete(&parser);
        return MHD_NO;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root && root->type == YAML_MAPPING_NODE) {
        for (yaml_node_pair_t* pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
            yaml_node_t *key = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value = yaml_document_get_node(&document, pair->value);

            if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE &&
                strcmp((const char*)key->data.scalar.value, "type") == 0 &&
                strcmp((const char*)value->data.scalar.value, "Create") == 0) {
                done_parsing = 1;
                break;
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    struct MHD_Response *response;
    if (done_parsing) {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    } else {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    }

    int ret = MHD_queue_response(connection, done_parsing ? MHD_HTTP_OK : MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}


Note: This code assumes you have `libmicrohttpd` and `libyaml` installed on your system. You can install them via package managers like apt, yum, etc., or from source.