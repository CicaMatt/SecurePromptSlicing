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

void free_session_data(struct MHD_Connection *connection) {
    struct SessionData *session = (struct SessionData *)MHD_get_connection_value(connection, MHD_COOKIE_KIND, "session_id");
    if (session != NULL) {
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
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup("john_doe");
    session->email = strdup("john.doe@example.com");
    session->ssn_last4 = strdup("1234");

    const char *page = "<html><body>"
                        "<h1>User Information</h1>"
                        "<p>Username: %s</p>"
                        "<p>Email: %s</p>"
                        "<p>Last 4 digits of SSN: %s</p>"
                        "</body></html>";

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer_asprintf(MHD_RESPMEM_MUST_FREE, page, session->username, session->email, session->ssn_last4);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free_session_data(connection);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}