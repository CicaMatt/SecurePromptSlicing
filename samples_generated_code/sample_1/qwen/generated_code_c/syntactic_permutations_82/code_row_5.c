#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct ConnectionInfo {
    char *payload;
};

void free_connection_info(void *cls) {
    struct ConnectionInfo *con_info = cls;
    if (con_info->payload) {
        free(con_info->payload);
    }
    free(con_info);
}

int parse_query_string(const char *query, struct MHD_Connection *connection) {
    const char *key = "payload";
    size_t key_len = strlen(key);
    struct ConnectionInfo *con_info = malloc(sizeof(struct ConnectionInfo));
    con_info->payload = NULL;

    if (MHD_get_connection_value(connection, MHD_GET_ARGUMENT_KIND, key)) {
        con_info->payload = strdup(MHD_get_connection_value(connection, MHD_GET_ARGUMENT_KIND, key));
    }

    MHD_add_connection_context(connection, __func__, con_info);
    return MHD_YES;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    parse_query_string(url, connection);

    struct ConnectionInfo *con_info = MHD_get_connection_context(connection, __func__);
    if (!con_info || !con_info->payload) {
        const char *error_message = "{\"error\": \"Payload not found\"}";
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST,
                                  MHD_create_response_from_buffer(strlen(error_message), (void *) error_message, MHD_RESPMEM_PERSISTENT));
    }

    // Assuming the payload is a simple "name=value" pair for demonstration
    const char *name_value = strstr(con_info->payload, "name=");
    if (!name_value) {
        const char *error_message = "{\"error\": \"Name not found in payload\"}";
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST,
                                  MHD_create_response_from_buffer(strlen(error_message), (void *) error_message, MHD_RESPMEM_PERSISTENT));
    }
    name_value += 5; // Move past "name="

    struct MHD_Response *response;
    char response_str[256];
    snprintf(response_str, sizeof(response_str), "{\"name\": \"%s\"}", name_value);
    response = MHD_create_response_from_buffer(strlen(response_str), (void *) response_str, MHD_RESPMEM_MUST_COPY);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_connection_info, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}