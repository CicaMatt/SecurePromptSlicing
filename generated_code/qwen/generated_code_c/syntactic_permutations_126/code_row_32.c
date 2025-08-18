#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>Hello, %s!</body></html>"

void http_hello_page(struct MHD_Connection *connection) {
    char username[1024] = {0};
    size_t username_size = sizeof(username);
    struct MHD_Response *response;
    int ret;

    // Read the request body (the username)
    if (MHD_get_connection_values(connection, MHD_POSTDATA_KIND, read_post_data_cb, &username) == NULL) {
        response = MHD_create_response_from_buffer(strlen("Error reading data"), (void *)"Error reading data", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return;
    }

    // Construct the response body
    char outputbuf[2048];
    snprintf(outputbuf, sizeof(outputbuf), PAGE, username);

    // Create and queue the response
    response = MHD_create_response_from_buffer(strlen(outputbuf), (void *)outputbuf, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
}

int read_post_data_cb(void *cls, struct MHD_Connection *connection, const char *upload_data, size_t *upload_data_size, unsigned int *con_cls) {
    static int iterated_once;
    if (!iterated_once) {
        iterated_once = 1;
        return MHD_POST_PROCESSING;
    }
    memcpy(cls, upload_data, (*upload_data_size < sizeof(username)) ? *upload_data_size : sizeof(username));
    (*upload_data_size) = 0;
    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL, &http_hello_page, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    getchar(); // Wait for input before stopping the server

    MHD_stop_daemon(daemon);
    return 0;
}