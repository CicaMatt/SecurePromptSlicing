#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct SessionData {
    char *username;
    char *email;
    char *ssn_last4;
};

void free_session_data(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    struct SessionData *session = (struct SessionData *) cls;
    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn_last4) free(session->ssn_last4);
    free(session);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup("testuser");
    session->email = strdup("test@example.com");
    session->ssn_last4 = strdup("1234");

    if (strcmp(url, "/info") == 0) {
        char response[512];
        snprintf(response, sizeof(response),
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>SSN Last 4: %s</p>"
                 "</body></html>",
                 session->username, session->email, session->ssn_last4);

        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
                strlen(response), (void*) response, MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}