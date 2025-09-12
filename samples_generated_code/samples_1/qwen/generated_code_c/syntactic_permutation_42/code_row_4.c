#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    if (strcmp(url, "/info") == 0) {
        char *response_str;
        asprintf(&response_str, "Username: %s\nEmail: %s\nSSN: %s",
                 session->username, session->email, session->ssn);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_str),
                                                                       (void *) response_str,
                                                                       MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main(int argc, char **argv) {
    struct SessionData session = {"john_doe", "john@example.com", "123-45-6789"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) &session,
                              MHD_OPTION_END);
    if (!daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}