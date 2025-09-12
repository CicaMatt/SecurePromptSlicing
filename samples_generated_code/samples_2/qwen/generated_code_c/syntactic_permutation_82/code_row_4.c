#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct Payload {
    char *name;
};

void free_payload(struct Payload *payload) {
    if (payload->name) {
        free(payload->name);
    }
}

int parse_query_string(const char *query, struct Payload *payload) {
    const char *key = "payload=";
    const char *value_start = strstr(query, key);
    if (!value_start) return MHD_NO;

    value_start += strlen(key);
    const char *value_end = strchr(value_start, '&');
    size_t length = (value_end ? value_end - value_start : strlen(value_start));

    payload->name = malloc(length + 1);
    if (!payload->name) return MHD_NO;
    strncpy(payload->name, value_start, length);
    payload->name[length] = '\0';

    return MHD_YES;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct Payload payload = {NULL};
    int ret = parse_query_string(url + strlen("/api?"), &payload);
    if (ret == MHD_NO)
        return MHD_NO;

    const char *response = payload.name ? payload.name : "Name not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);

    int status_code = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    free_payload(&payload);

    return status_code;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}