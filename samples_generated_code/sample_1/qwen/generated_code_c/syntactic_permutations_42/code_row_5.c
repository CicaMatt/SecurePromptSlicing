#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {
    struct SessionData *session = (struct SessionData *) cls;
    const char *page = "<html><body>User Info:<br>Username: %s<br>Email: %s<br>SSN: %s</body></html>";
    int ret;
    struct MHD_Response *response;

    if (strcmp(url, "/info") != 0 || strcmp(method, "GET") != 0)
        return MHD_NO;

    char *content = malloc(strlen(page) + strlen(session->username) + strlen(session->email) + strlen(session->ssn));
    sprintf(content, page, session->username, session->email, session->ssn);

    response = MHD_create_response_from_buffer(strlen(content), (void *) content, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct SessionData session_data = {"john_doe", "john@example.com", "123-45-6789"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) &session_data, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}