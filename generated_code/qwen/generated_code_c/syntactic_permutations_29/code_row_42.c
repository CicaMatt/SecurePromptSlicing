#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8888

int check_target(const char *target) {
    regex_t re;
    int reti;

    if (regcomp(&re, ".*\\..*", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&re, target, 0, NULL, 0);
    regfree(&re);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex match failed\n");
        exit(1);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *target = strchr(url + 1, '=');
    struct MHD_Response *response;
    int ret;

    if (NULL == target)
        return MHD_NO;

    target++;

    if (!aptr) {
        aptr = 1;
        return MHD_YES;
    }
    aptr = 0;

    char redirect_url[256];
    if (check_target(target)) {
        snprintf(redirect_url, sizeof(redirect_url), "http://%s", target);
    } else {
        strcpy(redirect_url, "/");
    }

    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, 302, response);
    MHD_add_response_header(response, "Location", redirect_url);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}