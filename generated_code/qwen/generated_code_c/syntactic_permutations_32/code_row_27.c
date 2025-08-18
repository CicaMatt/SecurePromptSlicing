#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
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

    const char *redirect_url = url + strlen("/redirect/");
    if (!redirect_invalid_url(redirect_url)) {
        char redirect_response[512];
        snprintf(redirect_response, sizeof(redirect_response),
                 "HTTP/1.1 302 Found\r\nLocation: %s\r\nConnection: close\r\n\r\n", redirect_url);
        return MHD_queue_response(connection, MHD_HTTP_FOUND,
                                  MHD_create_response_from_buffer(strlen(redirect_response),
                                                                  (void*)redirect_response, MHD_RESPMEM_PERSISTENT));
    }

    const char *response = ".";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), 
                                                                          (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
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