#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>Hello, %s!</body></html>"

void http_hello_page(struct MHD_Connection *connection) {
    const char* username = NULL;
    struct MHD_Response *response;
    char outputbuf[256];
    
    // Assuming the request body contains the username
    int post_data_size = 0;
    char* post_data = malloc(post_data_size);
    MHD_get_connection_values(connection, MHD_POSTDATA_KIND, &post_data, &post_data_size);

    if (post_data != NULL) {
        sscanf(post_data, "username=%s", outputbuf);
        free(post_data);
        snprintf(outputbuf, sizeof(outputbuf), PAGE, outputbuf);
    } else {
        snprintf(outputbuf, sizeof(outputbuf), PAGE, "Guest");
    }

    response = MHD_create_response_from_buffer(strlen(outputbuf),
                                                (void*)outputbuf,
                                                MHD_RESPMEM_PERSISTENT);
    MHD_add_response_header(response, "Content-Type", "text/html");
    MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/hello") == 0 && strcmp(method, "POST") == 0) {
        http_hello_page(connection);
        return MHD_YES;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                              NULL, NULL, &answer_to_connection,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar(); // Keep server running
    MHD_stop_daemon(daemon);
    return 0;
}