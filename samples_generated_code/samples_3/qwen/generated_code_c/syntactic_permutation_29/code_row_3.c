#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int check_url(const char *url) {
    regex_t re;
    int reti;

    reti = regcomp(&re, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&re, url, 0, NULL, 0);
    regfree(&re);

    return !reti;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *target = url + strlen("/redirect?url=");
    int is_valid = check_url(target);

    struct MHD_Response *response;
    const char *redirect_url = is_valid ? target : "/";

    response = MHD_create_response(302);
    MHD_add_response_header(response, "Location", redirect_url);
    int ret = MHD_queue_response(connection, 302, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}