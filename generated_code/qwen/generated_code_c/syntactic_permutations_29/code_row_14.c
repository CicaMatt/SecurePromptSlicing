#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "microhttpd.h"

#define PORT 8888

int check_url(const char *url) {
    regex_t re;
    int reti;

    reti = regcomp(&re, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&re, url, 0, NULL, 0);
    regfree(&re);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex match failed\n");
        exit(1);
    }
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    int valid_url = check_url(target);
    const char *redirect_url = valid_url ? target : "/";

    struct MHD_Response *response = MHD_create_response(0);
    MHD_add_response_header(response, "Location", redirect_url);
    int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}