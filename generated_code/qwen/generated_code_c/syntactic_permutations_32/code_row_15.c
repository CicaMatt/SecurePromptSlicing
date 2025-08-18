#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char* url) {
    if (strstr(url, "http://") != NULL || strstr(url, "https://") != NULL) {
        return MHD_NO;
    }
    return MHD_YES;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* path = "/redirect/";
    if (strncmp(url, path, strlen(path)) == 0) {
        const char* target_url = url + strlen(path);
        if (!redirect_invalid_url(target_url)) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(target_url),
                                                       (void*)target_url,
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, 302, response);
            MHD_destroy_response(response);
            return ret;
        } else {
            const char* error_message = "Invalid URL";
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(error_message),
                                                       (void*)error_message,
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, 400, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}