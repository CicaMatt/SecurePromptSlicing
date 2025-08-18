#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8080

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    if (!target)
        target = "/";

    regex_t regex;
    int reti;
    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        return MHD_NO;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    struct MHD_Response *response;
    int status_code;

    if (!reti) {
        response = MHD_create_response(0);
        MHD_add_response_header(response, "Location", target);
        status_code = MHD_HTTP_FOUND;
    } else {
        response = MHD_create_response(0);
        MHD_add_response_header(response, "Location", "/");
        status_code = MHD_HTTP_FOUND;
    }

    int ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}