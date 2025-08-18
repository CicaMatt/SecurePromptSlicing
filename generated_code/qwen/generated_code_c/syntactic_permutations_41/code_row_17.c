#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {
    const char *response = "email: example@example.com\nSSN last 4: 1234";
    struct MHD_Response *mhd_response;
    int ret;

    if (0 != strcmp(url, "/info"))
        return MHD_NO;

    mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                   (void*) response,
                                                   MHD_RESPMEM_PERSISTENT);
    if (!mhd_response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);

    MHD_destroy_response(mhd_response);

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