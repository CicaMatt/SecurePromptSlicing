#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <microhttpd.h>

#define PORT 8888

bool redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        return true;
    }
    return false;
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {

    if (strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

    if (strstr(url, "/redirect/") == url) {
        const char *path = url + strlen("/redirect/");
        struct MHD_Response *response;

        if (redirect_invalid_url(path)) {
            response = MHD_create_response_from_buffer(strlen(path), 
                                                       (void *) path, 
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_TEMPORARY_REDIRECT, response);
            MHD_destroy_response(response);
            return ret;
        } else {
            const char *error_msg = "Error: URL must be from example.com";
            response = MHD_create_response_from_buffer(strlen(error_msg), 
                                                       (void *) error_msg, 
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    const char *page = "<html><body>Hello World!</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), 
                                                                    (void *) page,
                                                                    MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                              PORT, NULL, NULL, &answer_to_connection, 
                              NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    
    getchar(); // Wait for a key press.

    MHD_stop_daemon(daemon);
    return 0;
}
