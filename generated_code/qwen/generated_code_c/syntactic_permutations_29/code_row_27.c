#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    const char *target = NULL;
    struct MHD_Response *response;
    int ret;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    if (!target)
        target = "/";

    regex_t regex;
    if (regcomp(&regex, ".*example\\.com.*", REG_EXTENDED) != 0) {
        response = MHD_create_response_from_buffer(strlen("Internal Server Error"), (void *)"Internal Server Error", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    int match = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (match != 0)
        target = "/";

    char redirect_url[1024];
    snprintf(redirect_url, sizeof(redirect_url), "http://localhost:%d%s", PORT, target);

    response = MHD_create_response_from_buffer(strlen("Redirecting..."), (void *)"Redirecting...", MHD_RESPMEM_PERSISTENT);
    MHD_add_response_header(response, "Location", redirect_url);
    ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &handler, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d...\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}