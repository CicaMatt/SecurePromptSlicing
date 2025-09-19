#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *error_message = "Error: Invalid domain.";
const char *domain_to_check = "example.com";

int redirect_invalid_url(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *query = strchr(url, '?');
    if (!query || query[1] == '\0')
        return MHD_NO;

    if (strstr(query + 1, domain_to_check)) {
        struct MHD_Response *response;
        response = MHD_create_response_for_redirect(MHD_HTTP_PERMANENT_REDIRECT, url);
        int ret = MHD_queue_response(connection, MHD_HTTP_PERMANENT_REDIRECT, response);
        MHD_destroy_response(response);
        return ret;
    }

    struct MHD_Response *error_response;
    error_response = MHD_create_response_from_buffer(strlen(error_message),
                                                      (void *)error_message,
                                                      MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, error_response);
    MHD_destroy_response(error_response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &redirect_invalid_url, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}