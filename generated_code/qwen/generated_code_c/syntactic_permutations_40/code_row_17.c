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
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    if (!session || !session->username || !session->email || !session->ssn_last4)
        return MHD_NO;

    const char *page_template =
        "<html>"
        "<head><title>Info Page</title></head>"
        "<body>"
        "<h1>User Information</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 of SSN: %s</p>"
        "</body>"
        "</html>";

    char *response_content = malloc(strlen(page_template) + strlen(session->username) +
                                     strlen(session->email) + strlen(session->ssn_last4) - 12);
    sprintf(response_content, page_template,
            session->username, session->email, session->ssn_last4);

    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(response_content),
                                               (void *) response_content,
                                               MHD_RESPMEM_MUST_FREE);
    if (!response) {
        free(response_content);
        return MHD_NO;
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    struct SessionData session;
    session.username = strdup("exampleUser");
    session.email = strdup("user@example.com");
    session.ssn_last4 = strdup("1234");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) &session,
                              MHD_OPTION_END);
    if (!daemon) {
        free(session.username);
        free(session.email);
        free(session.ssn_last4);
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    free(session.username);
    free(session.email);
    free(session.ssn_last4);

    return 0;
}