#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                 const char *url, const char *method,
                                 const char *version, const char *upload_data,
                                 size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info = cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO; // out of memory
        con_info->payload = NULL;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (0 != *upload_data_size) {
        con_info->payload = realloc(con_info->payload, strlen(upload_data) + 1);
        strcpy(con_info->payload, upload_data);
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char *response = "Error: payload not found";
    int ret;

    if (con_info->payload != NULL) {
        yaml_parser_t parser;
        yaml_document_t document;

        if (!yaml_parser_initialize(&parser))
            goto out;

        yaml_parser_set_input_string(&parser, (unsigned char *) con_info->payload, strlen(con_info->payload));

        if (!yaml_parser_load(&parser, &document)) {
            yaml_parser_delete(&parser);
            goto out;
        }

        yaml_node_t *root = yaml_document_get_root_node(&document);

        if (root && root->type == YAML_MAPPING_NODE) {
            for (int i = 0; i < root->data.mapping.pairs.top; i++) {
                yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
                yaml_node_t *key = yaml_document_get_node(&document, pair.key);
                yaml_node_t *value = yaml_document_get_node(&document, pair.value);

                if (key && key->type == YAML_SCALAR_NODE &&
                    value && value->type == YAML_SCALAR_NODE) {
                    if (strcmp((char *) key->data.scalar.value, "type") == 0 &&
                        strcmp((char *) value->data.scalar.value, "Create") == 0) {
                        response = "Error: type is Create";
                        break;
                    }
                }
            }

            yaml_document_delete(&document);
        }

        yaml_parser_delete(&parser);

    }

out:
    ret = MHD_queue_response(connection, MHD_HTTP_OK,
                             MHD_create_response_from_buffer(strlen(response),
                                                             (void *) response,
                                                             MHD_RESPMEM_MUST_COPY));
    free(con_info->payload);
    free(con_info);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}