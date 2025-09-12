#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    int ret;
    regex_t regex;
    regmatch_t pmatch[1];

    if (regcomp(&regex, "example\\.com", REG_EXTENDED | REG_ICASE)) {
        return MHD_NO;
    }

    if (target && !regexec(&regex, target, 1, pmatch, 0)) {
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND,
                                  MHD_create_response_from_buffer(strlen(target), (void*)target, MHD_RESPMEM_PERSISTENT));
    } else {
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND,
                                  MHD_create_response_from_buffer(1, "/", MHD_RESPMEM_PERSISTENT));
    }

    regfree(&regex);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}