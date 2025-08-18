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
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *target = strchr(url, '?');
    if (target != NULL) {
        target++; // move past the '?'
        const char *param_start = strstr(target, "target=");
        if (param_start != NULL) {
            param_start += 7; // length of "target="
            const char *param_end = strchr(param_start, '&');
            size_t param_length;
            if (param_end != NULL) {
                param_length = param_end - param_start;
            } else {
                param_length = strlen(param_start);
            }

            char target_value[param_length + 1];
            strncpy(target_value, param_start, param_length);
            target_value[param_length] = '\0';

            regex_t regex;
            int reti = regcomp(&regex, "^/[a-zA-Z0-9_/-]+$", REG_EXTENDED);
            if (reti) {
                fprintf(stderr, "Could not compile regex\n");
                return MHD_NO;
            }

            reti = regexec(&regex, target_value, 0, NULL, 0);
            regfree(&regex);

            struct MHD_Response *response;
            if (!reti) {
                response = MHD_create_response(302);
                char redirect_url[1024];
                snprintf(redirect_url, sizeof(redirect_url), "Location: %s", target_value);
                MHD_add_response_header(response, "Location", redirect_url);
            } else {
                response = MHD_create_response(302);
                MHD_add_response_header(response, "Location", "/");
            }

            int ret = MHD_queue_response(connection, 302, response);
            MHD_destroy_response(response);

            return ret;
        }
    }

    const char *page = "<html><body>Invalid request</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}