#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct MHD_Connection;

static int handle_api(void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls) {
    const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (query == NULL) {
        return MHD_NO;
    }

    // Simple key-value pair parsing
    char name[1024];
    sscanf(query, "name=%[^&]", name);

    const char *response = name;
    int ret_code = MHD YES;
    struct MHD_Response *ret = MHD_create_response_from_buffer(strlen(response),
                                                                (void *)response,
                                                                MHD_RESPMEM_PERSISTENT);
    if (!ret) {
        return MHD_NO;
    }

    int ret_value = MHD_queue_response(connection, MHD_HTTP_OK, ret);
    MHD_destroy_response(ret);

    return ret_value;
}

int main(void) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_api, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}