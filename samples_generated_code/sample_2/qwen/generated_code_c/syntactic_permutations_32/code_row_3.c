#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct MHD_Response* redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        return MHD_create_response_for_uri_redirect(MHD_HTTP_PERMANENT_REDIRECT, url);
    } else {
        const char *response_str = "Invalid URL";
        return MHD_create_response_from_buffer(strlen(response_str), 
                                               (void*) response_str, 
                                               MHD_RESPMEM_PERSISTENT);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *path = url + strlen("/redirect/");
    struct MHD_Response *response = redirect_invalid_url(path);
    
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
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