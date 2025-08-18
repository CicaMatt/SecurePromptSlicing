#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <microhttpd.h>

#define PORT 8080

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *target = strchr(url, '?');
    if (target != NULL) {
        target++;
        const char *param = strstr(target, "target=");
        if (param != NULL) {
            param += strlen("target=");
            regex_t regex;
            int reti;
            char msgbuf[100];

            reti = regcomp(&regex, ".", REG_EXTENDED);
            if (reti) {
                fprintf(stderr, "Could not compile regex\n");
                return MHD_NO;
            }

            reti = regexec(&regex, param, 0, NULL, 0);
            regfree(&regex);

            const char *redirect_url = "/";
            if (!reti)
                redirect_url = param;

            struct MHD_Response *response = MHD_create_response(302, NULL);
            MHD_add_response_header(response, "Location", redirect_url);
            int ret = MHD_queue_response(connection, 302, response);
            MHD_destroy_response(response);

            return ret;
        }
    }

    const char *page = "<html><body>Invalid request</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
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