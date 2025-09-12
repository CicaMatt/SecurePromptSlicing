#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    if (strstr(url, target_domain)) {
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

    if (strncmp(url, "/redirect/", 10) == 0) {
        const char *target_url = url + 10;
        if (redirect_invalid_url(target_url)) {
            const char *error_response = "Error: Invalid URL";
            struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_response),
                                                                             (void *) error_response,
                                                                             MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
            MHD_destroy_response(response);
            return ret;
        } else {
            struct MHD_Response *response = MHD_create_response(0);
            MHD_add_response_header(response, "Location", target_url);
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    const char *not_found = "Not Found";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found),
                                                                     (void *) not_found,
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
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