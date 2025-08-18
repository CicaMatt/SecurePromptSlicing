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
    (void) cls;
    (void) url;
    (void) version;
    (void) upload_data;
    (void) upload_data_size;

    if (strcmp(method, MHD_HTTP_METHOD_GET) != 0)
        return MHD_NO;

    const char *target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    if (!target)
        return MHD_NO;

    regex_t regex;
    int reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return MHD_NO;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    struct MHD_Response *response;
    int status_code;

    if (!reti) {
        response = MHD_create_response(0);
        status_code = MHD_HTTP_MOVED_PERMANENTLY;
        MHD_add_response_header(response, "Location", target);
    } else {
        const char *error_message = "Invalid target";
        response = MHD_create_response_from_buffer(strlen(error_message),
                                                   (void*) error_message,
                                                   MHD_RESPMEM_PERSISTENT);
        status_code = MHD_HTTP_BAD_REQUEST;
    }

    int ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}