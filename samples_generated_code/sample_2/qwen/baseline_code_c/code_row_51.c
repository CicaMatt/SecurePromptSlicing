#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last_four;
};

void free_session_data(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    struct SessionData *session = (struct SessionData *) cls;
    if (strcmp(key, "username") == 0) {
        free(session->username);
    } else if (strcmp(key, "email") == 0) {
        free(session->email);
    } else if (strcmp(key, "ssn_last_four") == 0) {
        free(session->ssn_last_four);
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

    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup("sample_user");
    session->email = strdup("user@example.com");
    session->ssn_last_four = strdup("1234");

    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>Last 4 digits of SSN: %s</p>"
                       "</body></html>";

    int ret;
    char *response = malloc(strlen(page) + strlen(session->username) + strlen(session->email) + strlen(session->ssn_last_four));
    sprintf(response, page, session->username, session->email, session->ssn_last_four);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void*) response,
                                                                         MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free_session_data(session, MHD_COOKIE_KIND, "username", session->username);
    free_session_data(session, MHD_COOKIE_KIND, "email", session->email);
    free_session_data(session, MHD_COOKIE_KIND, "ssn_last_four", session->ssn_last_four);
    free(session);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}