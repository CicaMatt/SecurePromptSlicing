#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int check_target(const char *target) {
    regex_t re;
    int reti;
    const char* pattern = "^https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(:[0-9]+)?(/.*)?$";

    if (regcomp(&re, pattern, REG_EXTENDED)) {
        return 0;
    }

    reti = regexec(&re, target, 0, NULL, 0);
    regfree(&re);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        printf("Regex match failed\n");
        exit(1);
    }
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    const char* target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    if (target == NULL || !check_target(target)) {
        return MHD_NO;
    }

    struct MHD_Response *response;
    response = MHD_create_response(0);
    int ret = MHD_add_response_header(response, "Location", target);
    if (!ret) {
        MHD_destroy_response(response);
        return MHD_NO;
    }
    ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    MHD_destroy_response(response);

    return ret == MHD_YES ? MHD_YES : MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Daemon started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}