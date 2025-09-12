#include <stdio.h>
#include <stdlib.h>
#include "microhttpd.h"

#define PORT 8888

struct MHD_Response *response;
struct MHD_Daemon *daemon;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/") != 0)
        return MHD_NO;
    response = MHD_create_response_from_buffer(strlen("Hello, World!"),
                                                (void*) "Hello, World!",
                                                MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main(int argc, char *const *argv) {
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}