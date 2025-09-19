#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        return MHD_YES;
    }
    return MHD_NO;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/redirect/") == url) {
        const char *target_url = url + strlen("/redirect/");
        int is_valid = redirect_invalid_url(target_url);
        
        if (is_valid) {
            struct MHD_Response *response;
            response = MHD_create_response(302);
            MHD_add_response_header(response, "Location", target_url);
            int ret = MHD_queue_response(connection, 302, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, 404, response);
    MHD_destroy_response(response);
    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Daemon started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}