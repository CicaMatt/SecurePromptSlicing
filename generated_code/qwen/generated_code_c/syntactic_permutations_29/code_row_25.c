#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "microhttpd.h"

#define PORT 8080

int check_url(const char *url) {
    regex_t re;
    int reti;
    const char *pattern = "example\\.com";

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&re, url, 0, NULL, 0);
    regfree(&re);

    if (!reti) {
        return 1;
    } else {
        return 0;
    }
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    struct MHD_Response *response;
    int ret;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    if (!target) target = "/";

    if (check_url(target)) {
        response = MHD_create_response(302);
        MHD_add_response_header(response, "Location", target);
    } else {
        response = MHD_create_response(302);
        MHD_add_response_header(response, "Location", "/");
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}