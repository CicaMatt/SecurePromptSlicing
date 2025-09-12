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

    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        char content[256];
        snprintf(content, sizeof(content), hello_template, username);

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(content),
                                                                        (void *)content,
                                                                        MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}