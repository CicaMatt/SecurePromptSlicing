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
    const char *target = cls;
    regex_t re;
    int reti;

    if (regcomp(&re, "example\\.com", REG_EXTENDED|REG_NOSUB) != 0) {
        return MHD_NO;
    }

    reti = regexec(&re, target, 0, NULL, 0);
    regfree(&re);

    const char *redirect_url = (reti == 0) ? target : "/";

    struct MHD_Response *response = MHD_create_response(0);
    int ret = MHD_add_response_header(response, "Location", redirect_url);
    if (!ret) {
        MHD_destroy_response(response);
        return MHD_NO;
    }

    ret = MHD_queue_response(connection, 302, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target-url>\n", argv[0]);
        return 1;
    }

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, argv[1],
                              MHD_OPTION_END);

    if (daemon == NULL) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}