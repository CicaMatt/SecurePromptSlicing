#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *page = "<html><body>Hello, %s!</body></html>";
    struct MHD_Response *response;
    int ret;
    char *outputbuf;
    char username[1024] = {0};

    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        size_t to_copy, req_str_len = sizeof(username) - 1;

        to_copy = *upload_data_size < req_str_len ? *upload_data_size : req_str_len;
        strncpy(username, upload_data, to_copy);
        username[to_copy] = '\0';
        *upload_data_size = 0;
        return MHD_YES;
    }

    outputbuf = malloc(strlen(page) + strlen(username));
    snprintf(outputbuf, strlen(page) + strlen(username), page, username);

    response = MHD_create_response_from_buffer(strlen(outputbuf),
                                               (void *)outputbuf,
                                               MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                              NULL, NULL,
                              &http_hello_page, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}