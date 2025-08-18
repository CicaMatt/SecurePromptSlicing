#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "microhttpd.h"

#define PORT 8888

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    const char *response;
    int ret;

    if (target != NULL) {
        regex_t regex;
        int regmatch_result;
        const char *pattern = "^http(s)?://[a-zA-Z0-9.-]+(:[0-9]+)?(/.*)?$";

        if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
            response = "/";
            ret = MHD_HTTP_MOVED_PERMANENTLY;
        } else {
            regmatch_result = regexec(&regex, target, 0, NULL, 0);
            if (regmatch_result == 0) {
                response = target;
                ret = MHD_HTTP_FOUND;
            } else {
                response = "/";
                ret = MHD_HTTP_MOVED_PERMANENTLY;
            }
            regfree(&regex);
        }
    } else {
        response = "/";
        ret = MHD_HTTP_MOVED_PERMANENTLY;
    }

    struct MHD_Response *mhd_response = MHD_create_response(0);
    MHD_add_response_header(mhd_response, "Location", response);
    int result = MHD_queue_response(connection, ret, mhd_response);
    MHD_destroy_response(mhd_response);
    return result;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}