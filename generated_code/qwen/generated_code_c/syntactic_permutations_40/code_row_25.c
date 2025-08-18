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

void free_session_data(void *cls) {
    struct SessionData *session = (struct SessionData *) cls;
    if (session) {
        free(session->username);
        free(session->email);
        free(session->ssn_last4);
        free(session);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = (struct SessionData *) cls;
    const char *response = "<html><body>"
                            "<h1>User Information</h1>"
                            "<p>Username: %s</p>"
                            "<p>Email: %s</p>"
                            "<p>SSN Last 4: %s</p>"
                            "</body></html>";

    char *page = malloc(strlen(response) + strlen(session->username) +
                         strlen(session->email) + strlen(session->ssn_last4) + 1);
    if (!page)
        return MHD_NO;

    sprintf(page, response, session->username, session->email, session->ssn_last4);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(page),
                                                                        (void *) page,
                                                                        MHD_RESPMEM_MUST_FREE);
    if (!response_obj) {
        free(page);
        return MHD_NO;
    }

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);

    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct SessionData *session = malloc(sizeof(struct SessionData));
    if (!session)
        return 1;

    session->username = strdup("john_doe");
    session->email = strdup("john.doe@example.com");
    session->ssn_last4 = strdup("5678");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT,
                                                  NULL, NULL,
                                                  &answer_to_connection, (void *) session,
                                                  MHD_OPTION_NOTIFY_COMPLETED, free_session_data, NULL,
                                                  MHD_OPTION_END);

    if (!daemon) {
        free_session_data(session);
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}