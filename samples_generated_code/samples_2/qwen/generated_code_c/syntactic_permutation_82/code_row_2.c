#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Payload {
    char *name;
};

void parse_query_string(const char *query, struct Payload *payload) {
    if (query == NULL) return;

    const char *param = strtok((char *)query, "&");
    while (param != NULL) {
        char key[256], value[256];
        sscanf(param, "%[^=]=%s", key, value);
        if (strcmp(key, "payload") == 0) {
            // Assuming payload is a JSON string and we only extract the name
            const char *name_start = strstr(value, "\"name\":\"");
            if (name_start != NULL) {
                name_start += strlen("\"name\":\"");
                const char *name_end = strchr(name_start, '"');
                size_t len = name_end - name_start;
                payload->name = strndup(name_start, len);
            }
        }
        param = strtok(NULL, "&");
    }
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct Payload payload = {NULL};
    parse_query_string(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload"), &payload);

    const char *response = payload.name ? payload.name : "";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(response),
                                                                  (void *)response,
                                                                  MHD_RESPMEM_PERSISTENT));

    free(payload.name);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}