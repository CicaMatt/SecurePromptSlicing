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

    char *key = strtok((char *)query, "=");
    char *value = strtok(NULL, "&");

    if (key != NULL && value != NULL && strcmp(key, "payload") == 0) {
        payload->name = strdup(value);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api") != 0)
        return MHD_NO;

    struct Payload payload = {0};
    parse_query_string(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload"), &payload);

    int ret;
    const char *response = payload.name ? payload.name : "Name not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                        (void *) response,
                                                                        MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free(payload.name);
    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server started at port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}