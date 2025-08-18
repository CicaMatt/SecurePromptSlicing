#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int http_hello_page(void *cls, struct MHD_Connection *connection,
                           const char *url, const char *method,
                           const char *version, const char *upload_data,
                           size_t *upload_data_size, void **con_cls) {
    static int upload_ready = 0;
    const char *username = "Guest";
    char outputbuf[256];
    struct MHD_Response *response;

    if (strcmp(method, "POST") != 0)
        return MHD_NO; // only POST is supported

    if (!upload_ready) {
        if (*upload_data_size == 0) {
            upload_ready = 1;
            return MHD_YES; // ask for more data
        }

        username = upload_data;
        *upload_data_size = 0;
        upload_ready = 0;
    }

    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    response = MHD_create_response_from_buffer(strlen(outputbuf), (void *)outputbuf,
                                                MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                &http_hello_page, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // keep server running

    MHD_stop_daemon(daemon);
    return 0;
}