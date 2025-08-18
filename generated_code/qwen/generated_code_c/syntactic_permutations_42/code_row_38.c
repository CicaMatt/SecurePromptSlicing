#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8080

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

int info_handler(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    if (!session || !session->username || !session->email || !session->ssn)
        return MHD_NO;

    char response[512];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
             session->username, session->email, session->ssn);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                        (void*)response,
                                                                        MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct SessionData session_data = {
        .username = "exampleUser",
        .email = "user@example.com",
        .ssn = "123-45-6789"
    };

    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info_handler, (void*)&session_data,
                              MHD_OPTION_END);
    if (!daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}