#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *error_message = "{\"error\": \"Invalid URL\"}";

int redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    if (strstr(url, valid_domain)) {
        return MHD_NO;
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

    const char *redirect_url = url + strlen("/redirect/");
    int is_invalid = redirect_invalid_url(redirect_url);

    struct MHD_Response *response;
    int ret;

    if (!is_invalid) {
        response = MHD_create_response_from_buffer(strlen(error_message),
                                                   (void *) error_message,
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    } else {
        response = MHD_create_response(0);
        MHD_add_response_header(response, "Location", redirect_url);
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
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

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}