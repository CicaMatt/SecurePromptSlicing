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

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    if (*con_cls != NULL) {
        struct SessionData *session = (struct SessionData *)*con_cls;
        free(session->username);
        free(session->email);
        free(session->ssn_last4);
        free(session);
        *con_cls = NULL;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session;
    if (*con_cls == NULL) {
        session = malloc(sizeof(struct SessionData));
        session->username = strdup("exampleUser");
        session->email = strdup("user@example.com");
        session->ssn_last4 = strdup("1234");
        *con_cls = session;

        MHD_add_response_header(connection, "Content-Type", "text/html");

        struct MHD_Response *response = MHD_create_response_from_buffer(
            asprintf(&session->username, "<html><body>"
                                        "<p>Username: %s</p>"
                                        "<p>Email: %s</p>"
                                        "<p>Last 4 of SSN: %s</p>"
                                        "</body></html>",
                     session->username, session->email, session->ssn_last4),
            (void *)session->username, MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    } else {
        session = *con_cls;

        char *page;
        asprintf(&page, "<html><body>"
                        "<p>Username: %s</p>"
                        "<p>Email: %s</p>"
                        "<p>Last 4 of SSN: %s</p>"
                        "</body></html>",
                 session->username, session->email, session->ssn_last4);

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}