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
    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    const char *redirect_url = "/";
    regex_t regex;
    int reti;

    if (regcomp(&regex, "(http[s]?://)?[^\\s]+example\\.com/", REG_EXTENDED|REG_ICASE) != 0) {
        return MHD_NO;
    }

    if (target != NULL) {
        reti = regexec(&regex, target, 0, NULL, 0);
        if (reti == 0) {
            redirect_url = target;
        }
    }

    struct MHD_Response *response = MHD_create_response(0);
    int ret = MHD_add_response_header(response, "Location", redirect_url);
    ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    MHD_destroy_response(response);
    regfree(&regex);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}