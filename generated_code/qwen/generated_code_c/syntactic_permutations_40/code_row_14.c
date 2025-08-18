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

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe) {
    struct SessionData *data = (struct SessionData *)cls;
    if (data) {
        free(data->username);
        free(data->email);
        free(data->ssn_last4);
        free(data);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    session_data->username = strdup("exampleUser");
    session_data->email = strdup("user@example.com");
    session_data->ssn_last4 = strdup("1234");

    const char *page = "<html><body>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>Last 4 of SSN: %s</p>"
                       "</body></html>";

    char *response_page = malloc(strlen(page) + strlen(session_data->username) +
                                  strlen(session_data->email) + strlen(session_data->ssn_last4));
    sprintf(response_page, page, session_data->username, session_data->email, session_data->ssn_last4);

    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(response_page),
                                               (void *)response_page,
                                               MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_add_connection_close_notifier(connection, session_data, free_session_data);

    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}