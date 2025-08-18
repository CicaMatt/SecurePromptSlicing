#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 1024

void http_hello_page(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int first_call = 1;
    const char *response_body_template = "<html><body>Hello, %s!</body></html>";
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[2048];
    struct MHD_Response *response;
    int ret;

    if (first_call) {
        first_call = 0;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        strncpy(username, upload_data, MAX_USERNAME_LENGTH - 1);
        username[MAX_USERNAME_LENGTH - 1] = '\0';
        *upload_data_size = 0;

        snprintf(outputbuf, sizeof(outputbuf), response_body_template, username);

        response = MHD_create_response_from_buffer(strlen(outputbuf), (void *)outputbuf, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }

    return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL, &http_hello_page, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server started on port 8080. Press Enter to stop the server.\n");
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}