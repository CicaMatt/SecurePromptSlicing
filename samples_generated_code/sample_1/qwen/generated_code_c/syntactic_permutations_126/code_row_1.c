#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void http_hello_page(struct MHD_Connection *connection, const char* username) {
    char response_body[256];
    snprintf(response_body, sizeof(response_body), "<html><body><h1>Hello, %s!</h1></body></html>", username);
    
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_body), (void*)response_body, MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header(response, "Content-Type", "text/html");
    MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/hello") != 0 || strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    if (*upload_data_size != 0) {
        http_hello_page(connection, upload_data);
        *upload_data_size = 0;
        return MHD_YES;
    }

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}