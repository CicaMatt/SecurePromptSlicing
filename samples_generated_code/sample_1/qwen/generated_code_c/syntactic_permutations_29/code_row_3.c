#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "microhttpd.h"

#define PORT 8888

int check_url(const char *url) {
    regex_t re;
    int reti;

    // Compile the regular expression for example.com
    reti = regcomp(&re, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    // Execute the regular expression
    reti = regexec(&re, url, 0, NULL, 0);
    regfree(&re);

    // If no match is found, redirect to /
    if (reti) {
        return 0;
    }
    return 1;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    const char *target = NULL;
    const char *response = "<html><body>Redirecting...</body></html>";
    int ret;

    // Extract the target parameter
    if (strcmp(method, "GET") == 0) {
        target = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "target");
    }

    struct MHD_Response *mhd_response;
    const char *redirect_url = "/";

    if (target && check_url(target)) {
        redirect_url = target;
    }

    mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, 302, mhd_response);
    MHD_add_response_header(mhd_response, "Location", redirect_url);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}