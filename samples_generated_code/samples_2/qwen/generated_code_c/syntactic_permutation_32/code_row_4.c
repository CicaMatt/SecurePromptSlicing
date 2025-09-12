#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        return MHD_HTTP_MOVED_PERMANENTLY;
    } else {
        return MHD_HTTP_BAD_REQUEST;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *redirect_url = "/"; // Redirect to root or any other URL
    int response_code;
    if (strncmp(url, "/redirect/", 10) == 0) {
        const char *target_url = url + 10;
        response_code = redirect_invalid_url(target_url);
        if (response_code == MHD_HTTP_MOVED_PERMANENTLY) {
            struct MHD_Response *response = MHD_create_response(0);
            MHD_add_response_header(response, "Location", redirect_url);
            int ret = MHD_queue_response(connection, response_code, response);
            MHD_destroy_response(response);
            return ret;
        }
    } else {
        response_code = MHD_HTTP_NOT_FOUND;
    }

    const char *error_message = "Invalid URL or method.";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message),
                                                                    (void *) error_message,
                                                                    MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, response_code, response);
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

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}