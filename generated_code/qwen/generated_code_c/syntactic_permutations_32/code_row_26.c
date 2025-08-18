#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        return MHD_HTTP_FOUND;
    }
    return MHD_HTTP_BAD_REQUEST;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    const char *redirect_url = url + strlen("/redirect/");
    int ret;
    struct MHD_Response *response;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/redirect/") == url) {
        ret = redirect_invalid_url(redirect_url);
        if (ret == MHD_HTTP_FOUND) {
            response = MHD_create_response(0);
            MHD_add_response_header(response, "Location", redirect_url);
        } else {
            response = MHD_create_response_from_buffer(strlen("Bad Request"), 
                                                      (void*) "Bad Request", 
                                                      MHD_RESPMEM_PERSISTENT);
        }
    } else {
        response = MHD_create_response_from_buffer(strlen("Not Found"), 
                                                  (void*) "Not Found", 
                                                  MHD_RESPMEM_PERSISTENT);
        ret = MHD_HTTP_NOT_FOUND;
    }

    int result = MHD_queue_response(connection, ret, response);
    MHD_destroy_response(response);

    return result;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d...\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}