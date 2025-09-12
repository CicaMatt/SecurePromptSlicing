#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *error_message = "Error: Invalid URL";

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        return MHD_YES;
    }
    return MHD_NO;
}

void send_error_response(struct MHD_Connection *connection) {
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(error_message), 
                                               (void*) error_message, 
                                               MHD_RESPMEM_PERSISTENT);
    MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *path = "/redirect/";
    if (strncmp(url, path, strlen(path)) == 0) {
        const char *target_url = url + strlen(path);
        if (redirect_invalid_url(target_url)) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", target_url);
            MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_destroy_response(response);
            return MHD_YES;
        } else {
            send_error_response(connection);
            return MHD_YES;
        }
    }

    return MHD_NO;
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