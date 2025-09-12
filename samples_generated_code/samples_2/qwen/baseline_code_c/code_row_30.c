#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(void *cls, struct MHD_Connection *connection, const char *url,
                     const char *method, const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int upload_pos;
    const char *username = NULL;
    char outputbuf[1024];
    struct MHD_Response *response;
    int ret;

    if (strcmp(method, "POST") != 0)
        return MHD_NO; // Only accept POST requests

    if (*upload_data_size != 0) {
        username = upload_data;
        *upload_data_size = 0;
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body>Hello, %s!</body></html>", username);
        response = MHD_create_response_from_buffer(strlen(outputbuf), (void*)outputbuf, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
    }

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &http_hello_page, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}