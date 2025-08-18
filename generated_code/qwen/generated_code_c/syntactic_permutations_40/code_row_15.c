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

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    if (!session || !session->username || !session->email || !session->ssn_last_four)
        return MHD_NO;

    const char *response = "<html><body>"
                           "<h1>User Information</h1>"
                           "<p>Username: %s</p>"
                           "<p>Email: %s</p>"
                           "<p>SSN Last 4: %s</p>"
                           "</body></html>";

    char buffer[500];
    snprintf(buffer, sizeof(buffer), response, session->username, session->email, session->ssn_last_four);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(buffer),
                                                                         (void *) buffer,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct SessionData session;
    session.username = "john_doe";
    session.email = "john.doe@example.com";
    session.ssn_last_four = "1234";

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, &session,
                                                 MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    free(session.username);
    free(session.email);
    free(session.ssn_last_four);

    return 0;
}