#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    const char *target = NULL;
    struct MHD_Response *response;
    int ret;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    if (!target)
        target = "/";

    regex_t regex;
    int regex_result;
    const char *regex_pattern = ".*example\\.com.*";
    regcomp(&regex, regex_pattern, REG_EXTENDED);
    regex_result = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (regex_result == 0) {
        response = MHD_create_response(0);
        MHD_add_response_header(response, "Location", target);
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response(0);
        MHD_add_response_header(response, "Location", "/");
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    }

    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}