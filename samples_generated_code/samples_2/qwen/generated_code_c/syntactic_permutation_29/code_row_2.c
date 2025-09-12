#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int check_url(const char *url) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return !reti;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    if (!target || !check_url(target))
        return MHD_NO;

    struct MHD_Response *response;
    response = MHD_create_response(302);
    MHD_add_response_header(response, "Location", target);
    int ret = MHD_queue_response(connection, 302, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (!daemon) {
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}