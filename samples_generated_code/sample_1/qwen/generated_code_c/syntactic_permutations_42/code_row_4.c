#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>User Info:<br>Username: %s<br>Email: %s<br>SSN: %s</body></html>"

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

void *create_session(const char *username, const char *email, const char *ssn) {
    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
    return session;
}

void destroy_session(void *cls) {
    struct SessionData *session = (struct SessionData *) cls;
    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct SessionData *session = create_session("exampleUser", "user@example.com", "123-45-6789");
        *con_cls = session;
        return MHD_YES;
    }

    struct SessionData *session = (struct SessionData *) *con_cls;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    char *response_page = malloc(strlen(PAGE) + strlen(session->username) + strlen(session->email) + strlen(session->ssn));
    sprintf(response_page, PAGE, session->username, session->email, session->ssn);

    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(response_page), (void*)response_page, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, destroy_session, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port 8080\n");

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}