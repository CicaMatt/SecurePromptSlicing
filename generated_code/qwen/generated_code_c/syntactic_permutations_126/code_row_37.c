#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

void http_hello_page(struct MHD_Connection *connection, const char* username) {
    char outputbuf[256];
    snprintf(outputbuf, sizeof(outputbuf), "<html><body>Hello, %s!</body></html>", username);
    
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(outputbuf), (void*)outputbuf, MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header(response, "Content-Type", "text/html");
    MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0 || strcmp(url, "/hello") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        *con_cls = malloc(*upload_data_size);
        memcpy(*con_cls, upload_data, *upload_data_size);
        return MHD_YES;
    }

    char* username = (char*)*con_cls;
    http_hello_page(connection, username);

    free(username);
    *con_cls = NULL;

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}