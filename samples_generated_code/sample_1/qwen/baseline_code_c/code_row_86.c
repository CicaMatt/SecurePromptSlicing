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
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    const char* payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload) {
        const char *response = "{\"error\": \"payload parameter is required\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        const char *response = "{\"error\": \"Failed to initialize YAML parser\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, mhd_response);
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    if (!yaml_parser_parse(&parser, &document)) {
        const char *response = "{\"error\": \"Failed to parse YAML\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        yaml_parser_delete(&parser);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (!root || root->type != YAML_MAPPING_NODE) {
        const char *response = "{\"error\": \"Invalid YAML format\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
    }

    for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
        yaml_node_item_t key = pair->key;
        yaml_node_item_t value = pair->value;

        if (document.nodes[key].type == YAML_SCALAR_NODE &&
            document.nodes[value].type == YAML_SCALAR_NODE &&
            strcmp((const char *)document.nodes[key].data.scalar.value, "type") == 0 &&
            strcmp((const char *)document.nodes[value].data.scalar.value, "Create") == 0) {
            const char *response = "{\"error\": \"Type Create is not allowed\"}";
            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
            yaml_document_delete(&document);
            yaml_parser_delete(&parser);
            return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    const char *response = "{\"message\": \"Request processed successfully\"}";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}