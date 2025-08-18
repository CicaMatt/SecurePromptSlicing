#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct MHD_Daemon *daemon;

char* get_value_from_payload(const char *payload, const char *key) {
    char *value = NULL;
    size_t key_len = strlen(key);
    while (1) {
        char *equals_pos = strchr(payload, '=');
        if (!equals_pos) break;
        size_t len = equals_pos - payload;
        if (len == key_len && strncmp(payload, key, key_len) == 0) {
            value = strdup(equals_pos + 1);
            break;
        }
        payload = equals_pos + 1;
        while (*payload && *payload != '&') payload++;
        if (*payload == '&') payload++;
    }
    return value;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method, const char *version,
            const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!query_string)
        return MHD_NO;

    char *name_value = get_value_from_payload(query_string, "name");

    struct MHD_Response *response;
    int ret;
    if (name_value) {
        response = MHD_create_response_from_buffer(strlen(name_value), (void *)name_value, MHD_RESPMEM_MUST_COPY);
        free(name_value);
    } else {
        const char *error_msg = "Name not found in payload";
        response = MHD_create_response_from_buffer(strlen(error_msg), (void *)error_msg, MHD_RESPMEM_PERSISTENT);
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (!daemon) {
        fprintf(stderr, "Failed to start daemon\n");
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}