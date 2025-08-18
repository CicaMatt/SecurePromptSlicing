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
    regex_t re;
    int reti;

    if (target == NULL)
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, NULL);

    reti = regcomp(&re, "example\\.com", REG_EXTENDED);
    if (reti) {
        regfree(&re);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, NULL);
    }

    reti = regexec(&re, target, 0, NULL, 0);
    regfree(&re);

    struct MHD_Response *response;
    if (!reti) {
        response = MHD_create_response_from_buffer(strlen(target), (void *)target, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_MOVED_PERMANENTLY, response);
    } else {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/");
        return MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}