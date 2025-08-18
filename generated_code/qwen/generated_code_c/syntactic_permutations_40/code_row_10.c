#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    const char *username;
    const char *email;
    const char *ssn;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {
    struct SessionData *session = cls;

    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>Last 4 digits of SSN: ****-%s</p>"
                       "</body></html>";

    char *response_page = malloc(strlen(page) + strlen(session->username) + strlen(session->email) + 5);
    if (!response_page)
        return MHD_NO;

    sprintf(response_page, page, session->username, session->email, session->ssn);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_page),
                                                                     (void *) response_page,
                                                                     MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct SessionData session_data = {
            .username = "john_doe",
            .email = "john.doe@example.com",
            .ssn = "1234"
    };

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                  &answer_to_connection, (void *) &session_data,
                                                  MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}