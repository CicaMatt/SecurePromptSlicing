#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    if (strstr(url, ".com") != NULL) {
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

    const char *path = &url[10]; // Skip "/redirect/"
    int is_invalid = redirect_invalid_url(path);

    struct MHD_Response *response;
    int ret;

    if (!is_invalid) {
        response = MHD_create_response(302);
        MHD_add_response_header(response, "Location", path);
    } else {
        response = MHD_create_response_from_buffer(strlen("Invalid URL"),
                                                   (void *)"Invalid URL",
                                                   MHD_RESPMEM_PERSISTENT);
    }

    ret = MHD_queue_response(connection, is_invalid ? 400 : 302, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char *const *argv) {
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