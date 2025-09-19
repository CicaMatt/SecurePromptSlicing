#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

void free_session_data(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    struct SessionData *session = (struct SessionData *) cls;
    if (strcmp(key, "username") == 0)
        free(session->username);
    else if (strcmp(key, "email") == 0)
        free(session->email);
    else if (strcmp(key, "ssn") == 0)
        free(session->ssn);
}

void *create_session_data(struct MHD_Connection *connection) {
    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup("exampleUser");
    session->email = strdup("user@example.com");
    session->ssn = strdup("123-45-6789");
    return session;
}

int info_handler(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = create_session_data(connection);

    char response[1024];
    snprintf(response, sizeof(response),
             "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}",
             session->username, session->email, session->ssn);

    int ret;
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free_session_data(session, MHD_COOKIE_KIND, "username", session->username);
    free_session_data(session, MHD_COOKIE_KIND, "email", session->email);
    free_session_data(session, MHD_COOKIE_KIND, "ssn", session->ssn);
    free(session);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}