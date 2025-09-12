#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int http_hello_page(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    static int first = 1;
    const char *username = "";
    const char *response_body_template = "<html><body>Hello, %s!</body></html>";
    char response_body[256];
    struct MHD_Response *response;
    int ret;

    if (first) {
        first = 0;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        username = upload_data;
        *upload_data_size = 0;
    } else {
        snprintf(response_body, sizeof(response_body), response_body_template, username);
        response = MHD_create_response_from_buffer(strlen(response_body),
                                                   (void *)response_body,
                                                   MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &http_hello_page, NULL, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}