#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void http_hello_page(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int first = 1;
    const char *username = NULL;
    const char *response = NULL;
    struct MHD_Response *mhd_response;
    int ret;

    if (first) {
        first = 0;
        return MHD_YES;
    }

    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*upload_data_size != 0) {
        username = upload_data;
        *upload_data_size = 0;
    } else
        return MHD_YES;

    char outputbuf[256];
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body>Hello, %s!</body></html>", username);

    mhd_response = MHD_create_response_from_buffer(strlen(outputbuf),
                                                    (void *)outputbuf,
                                                    MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                              NULL, NULL, &http_hello_page,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port 8888...\n");

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}