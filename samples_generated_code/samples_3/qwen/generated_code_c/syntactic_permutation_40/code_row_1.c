#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last4;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct MHD_Response *response;
    int ret;
    struct SessionData *session = (struct SessionData *) cls;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0) {
        char content[256];
        snprintf(content, sizeof(content),
                 "<html><body>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 of SSN: %s</p>"
                 "</body></html>",
                 session->username, session->email, session->ssn_last4);

        response = MHD_create_response_from_buffer(strlen(content),
                                                    (void *) content,
                                                    MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
    } else {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
    }

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;
    struct SessionData session;

    // Initialize session data
    session.username = "exampleUser";
    session.email = "user@example.com";
    session.ssn_last4 = "1234";

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) &session,
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}