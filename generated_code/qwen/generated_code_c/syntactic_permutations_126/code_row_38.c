#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int http_hello_page(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    static int first_call = 1;
    const char *username = "";
    char outputbuf[256];
    struct MHD_Response *response;

    if (first_call) {
        first_call = 0;
        return MHD_YES;
    }

    if (strcmp(method, "POST") != 0)
        return MHD_NO; // Only handle POST requests

    username = upload_data;

    snprintf(outputbuf, sizeof(outputbuf),
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);

    response = MHD_create_response_from_buffer(strlen(outputbuf), (void*)outputbuf, MHD_RESPMEM_PERSISTENT);
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
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}