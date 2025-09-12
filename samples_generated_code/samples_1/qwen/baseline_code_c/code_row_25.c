#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>Hello, %s!</body></html>"

void http_hello_page(struct MHD_Connection *connection) {
    char username[256];
    struct MHD_Response *response;
    const union MHD_ConnectionInfo *ci;
    int ret;

    ci = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_POST_PROCESSING);
    if (NULL == ci || 0 != ci->post_processing_finished)
        return;

    memset(username, 0, sizeof(username));
    ci = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_MEMORY_POOL);
    if (ci) {
        const char *data;
        size_t data_size;
        ci = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_POST_DATA);
        data = ci->post_processor->post_data;
        data_size = ci->post_processor->post_data_len;
        strncpy(username, data, sizeof(username) - 1);
    }

    char outputbuf[512];
    snprintf(outputbuf, sizeof(outputbuf), PAGE, username);

    response = MHD_create_response_from_buffer(strlen(outputbuf),
                                                (void*)outputbuf,
                                                MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/hello") == 0 && strcmp(method, "POST") == 0)
        http_hello_page(connection);
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              8888,
                              NULL,
                              NULL,
                              &answer_to_connection,
                              NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}