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
    const char *target = "/?target=";
    if (strncmp(url, target, strlen(target)) == 0) {
        const char *query = url + strlen(target);
        regex_t regex;
        int reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return MHD_NO;
        }
        reti = regexec(&regex, query, 0, NULL, 0);
        regfree(&regex);
        const char *redirect_url;
        if (!reti) {
            redirect_url = query;
        } else {
            redirect_url = "/";
        }
        struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_add_response_header(response, "Location", redirect_url);
        ret = MHD_queue_response(connection, 302, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    printf("Server started on port %d\n", PORT);
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}