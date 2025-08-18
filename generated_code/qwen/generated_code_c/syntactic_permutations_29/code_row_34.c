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
    const char *target = "";
    regex_t regex;
    int reti;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");

    if (regcomp(&regex, "^http[s]?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(:[0-9]+)?(/.*)?$", REG_EXTENDED) != 0)
        return MHD_NO;

    reti = regexec(&regex, target ? target : "", 0, NULL, 0);
    if (reti == 0) {
        struct MHD_Response *response;
        response = MHD_create_response(302);
        MHD_add_response_header(response, "Location", target);
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_destroy_response(response);
        regfree(&regex);
        return ret;
    } else {
        struct MHD_Response *response;
        response = MHD_create_response(302);
        MHD_add_response_header(response, "Location", "/");
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_destroy_response(response);
        regfree(&regex);
        return ret;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}