#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

static int handle_request(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    if (*upload_data_size == 0) {
        return MHD_YES;
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        return MHD_NO;
    }
    yaml_parser_set_input_string(&parser, upload_data, *upload_data_size);

    int done = 0;
    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        return MHD_NO;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root == NULL) {
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        return MHD_NO;
    }

    const char *payload_key = "payload";
    int payload_found = 0;
    for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
        yaml_node_t *key = yaml_document_get_node(&document, pair->key);
        if (key != NULL && key->type == YAML_SCALAR_NODE &&
            strcmp((const char *)key->data.scalar.value, payload_key) == 0) {
            payload_found = 1;
            break;
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    const char *response;
    int response_status;

    if (!payload_found) {
        response = "{\"error\": \"missing payload parameter\"}";
        response_status = MHD_HTTP_BAD_REQUEST;
    } else {
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(&parser, upload_data, *upload_data_size);

        if (!yaml_parser_load(&parser, &document)) {
            yaml_parser_delete(&parser);
            return MHD_NO;
        }

        root = yaml_document_get_root_node(&document);
        if (root == NULL) {
            yaml_document_delete(&document);
            yaml_parser_delete(&parser);
            return MHD_NO;
        }

        const char *type_key = "type";
        int type_found = 0;
        for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
            yaml_node_t *key = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value = yaml_document_get_node(&document, pair->value);
            if (key != NULL && key->type == YAML_SCALAR_NODE &&
                strcmp((const char *)key->data.scalar.value, type_key) == 0 &&
                value != NULL && value->type == YAML_SCALAR_NODE &&
                strcmp((const char *)value->data.scalar.value, "Create") == 0) {
                type_found = 1;
                break;
            }
        }

        yaml_document_delete(&document);
        yaml_parser_delete(&parser);

        if (type_found) {
            response = "{\"error\": \"invalid request type\"}";
            response_status = MHD_HTTP_BAD_REQUEST;
        } else {
            response = "{\"status\": \"success\"}";
            response_status = MHD_HTTP_OK;
        }
    }

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, response_status, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}