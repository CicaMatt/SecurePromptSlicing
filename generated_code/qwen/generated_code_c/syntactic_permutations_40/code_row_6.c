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

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    struct SessionData *session = (struct SessionData *)*con_cls;
    if (session != NULL) {
        free(session->username);
        free(session->email);
        free(session->ssn_last_four);
        free(session);
    }
}

int info_handler(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup("exampleUser");
    session->email = strdup("user@example.com");
    session->ssn_last_four = strdup("1234");

    *con_cls = session;
    MHD_add_response_header(connection, "Content-Type", "text/html");

    char response[500];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session->username, session->email, session->ssn_last_four);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY));
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_session_data,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}