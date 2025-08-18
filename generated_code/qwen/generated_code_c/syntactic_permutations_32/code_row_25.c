#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain) != NULL) {
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

    const char *path = "/redirect/";
    if (strncmp(url, path, strlen(path)) == 0) {
        const char *url_param = url + strlen(path);
        if (redirect_invalid_url(url_param)) {
            const char *error_message = "Error: Invalid URL";
            struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message),
                                                                             (void*) error_message,
                                                                             MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
            MHD_destroy_response(response);
            return ret;
        } else {
            struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", url_param);
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    const char *not_found_message = "Not Found";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found_message),
                                                                     (void*) not_found_message,
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}