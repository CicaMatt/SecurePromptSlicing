#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char username[256] = {0};
    if (sscanf(url, "/hello/%255s", username) == 1) {
        char response[512];
        snprintf(response, sizeof(response), "<html><body><h1>Hello, %s!</h1></body></html>", username);

        struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                             (void*)response,
                                                                             MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
        MHD_destroy_response(response_obj);
        return ret;
    }

    return MHD_NO;
}

int main() {
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