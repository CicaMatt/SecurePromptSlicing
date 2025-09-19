#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

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
    struct SessionData *session = (struct SessionData *) cls;

    if (strcmp(url, "/info") == 0 && strcmp(method, MHD_HTTP_METHOD_GET) == 0) {
        const char *page = "<html><body>"
                           "<h1>User Information</h1>"
                           "<p>Username: %s</p>"
                           "<p>Email: %s</p>"
                           "<p>Last 4 digits of SSN: %s</p>"
                           "</body></html>";
        char buffer[512];
        snprintf(buffer, sizeof(buffer), page, session->username, session->email, session->ssn_last4);

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer),
                                                                        (void *) buffer,
                                                                        MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;
    struct SessionData session;

    // Example data for demonstration purposes
    session.username = "johndoe";
    session.email = "john.doe@example.com";
    session.ssn_last4 = "1234";

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) &session, MHD_OPTION_END);
    if (daemon == NULL) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    free(session.username);
    free(session.email);
    free(session.ssn_last4);

    return 0;
}