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
    regex_t regex;
    int reti;

    if (regcomp(&regex, "example\\.com", REG_EXTENDED|REG_ICASE)) {
        return MHD_NO;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    const char *redirect_url = (reti == 0) ? target : "/";

    struct MHD_Response *response = MHD_create_response(0);
    int ret = MHD_add_response_header(response, "Location", redirect_url);
    if (ret != MHD_YES) {
        MHD_destroy_response(response);
        return MHD_NO;
    }

    ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    MHD_destroy_response(response);

    return ret == MHD_YES ? MHD_YES : MHD_NO;
}

int main(int argc, char *const *argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target-url>\n", argv[0]);
        return 1;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                                               PORT, NULL, NULL,
                                               &answer_to_connection, argv[1],
                                               MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}