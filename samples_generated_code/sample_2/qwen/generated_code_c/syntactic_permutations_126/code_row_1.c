#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void http_hello_page(struct MHD_Connection *connection) {
    const char *username = NULL;
    char *response_body = NULL;
    size_t response_size = 0;
    struct MHD_Response *response;
    int ret;

    // Read the request body (username)
    username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");

    if (username == NULL) {
        username = "Guest";
    }

    // Construct the response body
    response_size = snprintf(NULL, 0, "<html><body><h1>Hello, %s!</h1></body></html>", username);
    response_body = malloc(response_size + 1);
    snprintf(response_body, response_size + 1, "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Create the response
    response = MHD_create_response_from_buffer(response_size, (void *)response_body, MHD_RESPMEM_MUST_FREE);

    // Send the response
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") == 0 && strcmp(url, "/hello") == 0) {
        http_hello_page(connection);
        return MHD_YES;
    }
    return MHD_NO;
}

int main(int argc, char const *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}