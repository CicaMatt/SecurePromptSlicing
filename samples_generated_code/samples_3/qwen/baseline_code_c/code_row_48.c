#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <yaml.h>

#define PORT 5000

struct connection_info_struct {
    char * payload;
};

int check_yaml_type(const char * yaml_data) {
    yaml_parser_t parser;
    yaml_token_t token;
    int is_create = 0;

    if (!yaml_parser_initialize(&parser)) {
        return 0;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_data, strlen(yaml_data));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            break;
        }
        if (token.type == YAML_SCALAR_TOKEN && strcmp((char *)token.data.scalar.value, "Create") == 0) {
            is_create = 1;
        }
        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);

    return is_create;
}

int answer_to_connection(void * cls, struct MHD_Connection * connection,
                         const char * url, const char * method,
                         const char * version, const char * upload_data,
                         size_t * upload_data_size, void ** con_cls) {
    struct connection_info_struct *con_info = (struct connection_info_struct*)*con_cls;

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        con_info->payload = NULL;
        *con_cls = con_info;
        return MHD_YES;
    }

    const char* payload_query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (payload_query == NULL) {
        const char * response = "{\"error\": \"Missing payload parameter\"}";
        struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response_object);
        MHD_destroy_response(response_object);
        free(con_info);
        return ret;
    }

    if (*upload_data_size != 0) {
        con_info->payload = realloc(con_info->payload, *upload_data_size + 1);
        strcpy(con_info->payload, upload_data);
        *upload_data_size = 0;
        return MHD_YES;
    }

    int is_create = check_yaml_type(con_info->payload);
    if (is_create) {
        const char * response = "{\"error\": \"Type Create not allowed\"}";
        struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response_object);
        MHD_destroy_response(response_object);
    } else {
        const char * response = "{\"status\": \"success\"}";
        struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
        MHD_destroy_response(response_object);
    }

    free(con_info->payload);
    free(con_info);
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}