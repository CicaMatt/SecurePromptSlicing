#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int check_target(const char *target) {
    regex_t regex;
    int reti;
    const char *pattern = ".*example\\.com.*";

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

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
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    const char *redirect_url = "/";

    if (target && check_target(target)) {
        redirect_url = target;
    }

    struct MHD_Response *response = MHD_create_response(0);
    int ret = MHD_add_response_header(response, "Location", redirect_url) &&
              MHD_queue_response(connection, 302, response);

    MHD_destroy_response(response);
    return ret ? MHD_YES : MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    fprintf(stdout, "Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}