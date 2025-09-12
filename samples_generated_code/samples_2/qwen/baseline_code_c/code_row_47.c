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
    const char *target = strchr(url, '?');
    if (target != NULL) {
        target++;
        target = strstr(target, "target=");
        if (target != NULL) {
            target += 7;
            regex_t regex;
            int reti;
            char msgbuf[100];

            reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
            if (reti) {
                fprintf(stderr, "Could not compile regex\n");
                exit(1);
            }

            reti = regexec(&regex, target, 0, NULL, 0);
            regfree(&regex);

            const char *redirect_url;
            if (!reti) {
                redirect_url = target;
            } else {
                redirect_url = "/";
            }

            struct MHD_Response *response;
            response = MHD_create_response(0);
            MHD_add_response_header(response, "Location", redirect_url);
            int ret = MHD_queue_response(connection, MHD_HTTP_MOVED_PERMANENTLY, response);
            MHD_destroy_response(response);

            return ret;
        }
    }

    struct MHD_Response *response;
    const char *page = "<html><body>Invalid request</body></html>";
    response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}