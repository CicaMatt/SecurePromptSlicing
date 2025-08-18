#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>Hello, %s!</body></html>"

int http_hello_page(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    static int first = 1;
    const char* username = "Guest";
    const char* response_body;
    struct MHD_Response *response;
    int ret;

    if (0 != strcmp(url, "/hello"))
        return MHD_NO;

    if (first) {
        first = 0;
        if (*upload_data_size != 0) {
            username = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }
    } else {
        first = 1;
        response_body = malloc(strlen(PAGE) + strlen(username));
        sprintf((char*)response_body, PAGE, username);
        response = MHD_create_response_from_buffer(strlen(response_body),
                                                   (void *)response_body,
                                                   MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_YES;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &http_hello_page, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}