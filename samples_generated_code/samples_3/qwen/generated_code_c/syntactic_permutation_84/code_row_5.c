#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

    const char* payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload) {
        const char* error_message = "{\"error\": \"Missing payload parameter\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void*)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        const char* error_message = "{\"error\": \"Failed to initialize YAML parser\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void*)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        const char* error_message = "{\"error\": \"Failed to parse YAML\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void*)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        yaml_parser_delete(&parser);
        return ret;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (!root || root->type != YAML_MAPPING_NODE) {
        const char* error_message = "{\"error\": \"Invalid YAML format\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void*)error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        return ret;
    }

    const char* type_value = NULL;
    for (int i = 0; i < root->data.mapping.pairs.top; i++) {
        yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
        yaml_node_t *key = yaml_document_get_node(&document, pair.key);
        yaml_node_t *value = yaml_document_get_node(&document, pair.value);

        if (key->type == YAML_SCALAR_NODE && strcmp((const char*)key->data.scalar.value, "type") == 0) {
            if (value->type == YAML_SCALAR_NODE) {
                type_value = (const char*)value->data.scalar.value;
                break;
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    if (!type_value || strcmp(type_value, "Create") != 0) {
        const char* response_message = "{\"status\": \"success\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_message), (void*)response_message, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, response);
    } else {
        const char* error_message = "{\"error\": \"Type Create is not allowed\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void*)error_message, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}