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
    if (strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    const char* payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload) {
        const char *error_message = "{\"error\": \"No payload parameter\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), 
                                                                       (void*) error_message, 
                                                                       MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        const char *error_message = "{\"error\": \"Failed to initialize YAML parser\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), 
                                                                       (void*) error_message, 
                                                                       MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        const char *error_message = "{\"error\": \"Failed to parse YAML\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), 
                                                                       (void*) error_message, 
                                                                       MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        yaml_parser_delete(&parser);
        return ret;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (int i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
            yaml_node_t *key_node = yaml_document_get_node(&document, pair.key);
            if (key_node->type == YAML_SCALAR_NODE && 
                strcmp((const char *)key_node->data.scalar.value, "type") == 0) {
                yaml_node_t *value_node = yaml_document_get_node(&document, pair.value);
                if (value_node->type == YAML_SCALAR_NODE && 
                    strcmp((const char *)value_node->data.scalar.value, "Create") == 0) {
                    const char *error_message = "{\"error\": \"Type is Create\"}";
                    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), 
                                                                                   (void*) error_message, 
                                                                                   MHD_RESPMEM_PERSISTENT);
                    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
                    MHD_destroy_response(response);
                    yaml_document_delete(&document);
                    yaml_parser_delete(&parser);
                    return ret;
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    const char *success_message = "{\"message\": \"Success\"}";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(success_message), 
                                                                   (void*) success_message, 
                                                                   MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, 
                              MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}