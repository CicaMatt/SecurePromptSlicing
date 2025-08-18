#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void http_hello_page(struct MHD_Connection *connection, const char* username) {
    char outputbuf[1024];
    int ret;
    struct MHD_Response *response;

    snprintf(outputbuf, sizeof(outputbuf), "<html><body><h1>Hello, %s!</h1></body></html>", username);

    response = MHD_create_response_from_buffer(strlen(outputbuf), (void*)outputbuf, MHD_RESPMEM_MUST_COPY);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char* username;

    if (0 != strcmp(method, "POST"))
        return MHD_NO; // unexpected method

    if (&aptr != *con_cls) {
        /* do never respond on first call */
        *con_cls = &aptr;
        return MHD_YES;
    }
    *con_cls = NULL;

    username = upload_data;
    http_hello_page(connection, username);

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // wait for keypress

    MHD_stop_daemon(daemon);
    return 0;
}