#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

#define PAGE "<html><body>User Info:<br>Username: %s<br>Email: %s<br>SSN: %s</body></html>"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct SessionData *session = (struct SessionData *) cls;

    if (strcmp(method, "GET") != 0)
        return MHD_NO; // Method not allowed

    if (strcmp(url, "/info") != 0)
        return MHD_NO; // URL not found

    char *page = malloc(strlen(PAGE) + strlen(session->username) + strlen(session->email) + strlen(session->ssn));
    sprintf(page, PAGE, session->username, session->email, session->ssn);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct SessionData session;
    session.username = strdup("john_doe");
    session.email = strdup("john@example.com");
    session.ssn = strdup("123-45-6789");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                                                  &answer_to_connection, (void *) &session,
                                                  MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar(); // Wait for user input

    MHD_stop_daemon(daemon);

    free(session.username);
    free(session.email);
    free(session.ssn);

    return 0;
}