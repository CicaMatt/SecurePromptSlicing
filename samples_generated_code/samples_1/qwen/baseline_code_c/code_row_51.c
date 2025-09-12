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

void free_session_data(void *cls) {
    struct SessionData *data = (struct SessionData *) cls;
    free(data->username);
    free(data->email);
    free(data->ssn_last4);
    free(data);
}

int info_handler(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = (struct SessionData *) cls;
    if (!session)
        return MHD_NO;

    const char *response_format =
            "<html><body>"
            "<h1>User Information</h1>"
            "<p>Username: %s</p>"
            "<p>Email: %s</p>"
            "<p>Last 4 digits of SSN: %s</p>"
            "</body></html>";

    char *response = malloc(strlen(response_format) + strlen(session->username) +
                           strlen(session->email) + strlen(session->ssn_last4));
    if (!response)
        return MHD_NO;

    sprintf(response, response_format, session->username, session->email, session->ssn_last4);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    struct SessionData *session = malloc(sizeof(struct SessionData));
    if (!session)
        return 1;

    session->username = strdup("john_doe");
    session->email = strdup("john.doe@example.com");
    session->ssn_last4 = strdup("5678");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info_handler, (void *) session, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}