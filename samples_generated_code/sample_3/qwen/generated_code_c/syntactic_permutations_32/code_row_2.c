#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int validate_url(const char *url) {
    // Simple validation: check if the URL starts with http:// or https://
    return (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0);
}

void redirect_invalid_url(struct MHD_Connection *connection, const char *url) {
    int ret;
    struct MHD_Response *response;

    if (validate_url(url)) {
        response = MHD_create_response(0);
        MHD_add_response_header(response, "Location", url);
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Invalid URL"), (void*)"Invalid URL", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    }

    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    // Extract the URL parameter
    const char *path = MHD_lookup_connection_value(connection, MHD_REQUEST_URI_LOGGED, NULL);
    const char *prefix = "/redirect/";
    if (strncmp(path, prefix, strlen(prefix)) == 0) {
        redirect_invalid_url(connection, path + strlen(prefix));
        return MHD_YES;
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}