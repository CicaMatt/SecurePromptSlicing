#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

struct MHD_PostProcessor *postprocessor;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        postprocessor = MHD_create_post_processor(connection, 1024, NULL, NULL);
        *con_cls = (void*)1;
        return MHD_YES;
    }

    if (postprocessor != NULL && *upload_data_size != 0) {
        MHD_post_process(postprocessor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        return MHD_YES;
    }

    yaml_parser_t parser;
    yaml_document_t document;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, upload_data, strlen(upload_data));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_emitter_delete(&parser);
        return MHD_NO;
    }

    int payload_found = 0;
    int create_type = 0;

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root->type == YAML_MAPPING_NODE) {
        for (int i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
            yaml_node_t *key = yaml_document_get_node(&document, pair.key);
            yaml_node_t *value = yaml_document_get_node(&document, pair.value);

            if (key->type == YAML_SCALAR_NODE && strcmp((char*)key->data.scalar.value, "payload") == 0) {
                payload_found = 1;

                if (value->type == YAML_MAPPING_NODE) {
                    for (int j = 0; j < value->data.mapping.pairs.top; j++) {
                        yaml_node_pair_t typePair = value->data.mapping.pairs.items[j];
                        yaml_node_t *typeKey = yaml_document_get_node(&document, typePair.key);
                        yaml_node_t *typeValue = yaml_document_get_node(&document, typePair.value);

                        if (typeKey->type == YAML_SCALAR_NODE && strcmp((char*)typeKey->data.scalar.value, "type") == 0 &&
                            typeValue->type == YAML_SCALAR_NODE && strcmp((char*)typeValue->data.scalar.value, "Create") == 0) {
                            create_type = 1;
                        }
                    }
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    if (!payload_found) {
        const char *response = "{\"error\": \"No payload parameter found\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    } else if (create_type) {
        const char *response = "{\"error\": \"Type Create is not allowed\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    const char *response = "OK";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
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