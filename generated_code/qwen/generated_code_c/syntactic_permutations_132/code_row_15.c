#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *hello_template = "<html><body><h1>Hello, %s!</h1></body></html>";

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/hello/") == url) {
        const char *username = url + strlen("/hello/");
        char *response;
        response = malloc(strlen(hello_template) + strlen(username));
        sprintf(response, hello_template, username);

        struct MHD_Response *mhd_response;
        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                       (void*) response,
                                                       MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}