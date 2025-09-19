#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *error_message = "Invalid URL";

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        return MHD_NO; // No redirection logic implemented here as libmicrohttpd does not support it directly in this context
    } else {
        return MHD_YES;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret = redirect_invalid_url(url);
    struct MHD_Response *response;
    if (ret == MHD_YES) {
        response = MHD_create_response_from_buffer(strlen(error_message),
                                                   (void *) error_message,
                                                   MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    } else {
        // In a real-world scenario, you would handle redirection here
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, response);
    }

    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}