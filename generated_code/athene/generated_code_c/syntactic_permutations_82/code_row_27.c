#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct MHD_Daemon *daemon;

char* get_query_value(const char *query, const char *key) {
    char *value = NULL;
    size_t key_len = strlen(key);
    while (*query) {
        if (strncmp(query, key, key_len) == 0 && query[key_len] == '=') {
            value = strdup(query + key_len + 1);
            break;
        }
        query = strchr(query, '&');
        if (!query) break;
        query++;
    }
    return value;
}

int handle_api(void *cls, struct MHD_Connection *connection,
               const char *url, const char *method, const char *version,
               const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!query) {
        const char *response = "{\"error\": \"Missing payload parameter\"}";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
    }

    char *payload = get_query_value(query, "payload");
    if (!payload) {
        const char *response = "{\"error\": \"Invalid payload format\"}";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
    }

    char *name_value = get_query_value(payload, "name");
    if (!name_value) {
        const char *response = "{\"error\": \"Name not found in payload\"}";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        free(payload);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
    }

    char response[128];
    snprintf(response, sizeof(response), "{\"name\": \"%s\"}", name_value);

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);

    free(payload);
    free(name_value);

    return ret;
}

int main() {
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_api, NULL, MHD_OPTION_END);
    if (!daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}