#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Payload {
    char *name;
};

void free_payload(struct Payload *payload) {
    if (payload->name != NULL) {
        free(payload->name);
    }
    free(payload);
}

struct Payload* parse_query_string(const char *query_string) {
    struct Payload *payload = malloc(sizeof(struct Payload));
    payload->name = NULL;

    if (query_string == NULL) return payload;

    char *query_copy = strdup(query_string);
    char *key_value_pair = strtok(query_copy, "&");
    while (key_value_pair != NULL) {
        char *key = strtok(key_value_pair, "=");
        char *value = strtok(NULL, "=");
        if (strcmp(key, "payload") == 0 && value != NULL) {
            payload->name = strdup(value);
        }
        key_value_pair = strtok(NULL, "&");
    }
    free(query_copy);

    return payload;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api") != 0) {
        return MHD_NO;
    }

    struct Payload *payload = parse_query_string(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload"));

    const char *response = payload->name ? payload->name : "";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                 MHD_create_response_from_buffer(strlen(response),
                                                                 (void *) response,
                                                                 MHD_RESPMEM_PERSISTENT));

    free_payload(payload);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}