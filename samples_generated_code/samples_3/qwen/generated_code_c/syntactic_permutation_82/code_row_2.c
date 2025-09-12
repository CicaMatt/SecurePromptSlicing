#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ResponseData {
    const char *name;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct ResponseData *response_data = cls;
    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");

    if (!payload || strcmp(payload, response_data->name) != 0) {
        return MHD_NO;
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_data->name),
                                                                      (void *) strdup(response_data->name),
                                                                      MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct ResponseData data = {"exampleName"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) &data,
                              MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}