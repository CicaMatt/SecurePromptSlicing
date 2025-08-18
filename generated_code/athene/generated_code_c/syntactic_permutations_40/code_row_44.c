#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct ConnectionInfo {
    char *username;
    char *email;
    char *ssn;
};

static int info(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfo *info = (struct ConnectionInfo *) cls;
    char response[256];
    snprintf(response, sizeof(response), 
             "Username: %s<br>Email: %s<br>Last 4 digits of SSN: %s",
             info->username, info->email, &info->ssn[strlen(info->ssn) - 4]);

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                 (void *)response,
                                                                 MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
    return ret;
}

int main(void) {
    struct ConnectionInfo info = {"john_doe", "john.doe@example.com", "123456789"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &info, info, MHD_OPTION_END);
    if (daemon == NULL) {
        return 1;
    }

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    free(info.username);
    free(info.email);
    free(info.ssn);

    return 0;
}