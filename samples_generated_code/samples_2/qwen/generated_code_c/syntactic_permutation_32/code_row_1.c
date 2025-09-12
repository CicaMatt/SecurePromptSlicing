#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        return MHD_NO; // URL is valid, do not intercept
    } else {
        return MHD_YES; // URL is invalid, send error message
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *redirect_url = url + strlen("/redirect/");
    int is_invalid = redirect_invalid_url(redirect_url);

    if (!is_invalid) {
        struct MHD_Response *response = MHD_create_response_from_buffer(
            0, NULL, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, 302, response);
        MHD_add_response_header(response, "Location", redirect_url);
        MHD_destroy_response(response);
        return ret;
    } else {
        const char *error_message = "<html><body>Invalid URL</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(
            strlen(error_message), (void *) error_message, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, 400, response);
        MHD_destroy_response(response);
        return ret;
    }
}

int main() {
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