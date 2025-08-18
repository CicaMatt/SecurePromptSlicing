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

void free_session_data(struct SessionData *data) {
    free(data->username);
    free(data->email);
    free(data->ssn_last_four);
    free(data);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0 || strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup("exampleUser");
    session->email = strdup("user@example.com");
    session->ssn_last_four = strdup("1234");

    const char *page =
            "<html><body>"
            "<h1>User Information</h1>"
            "<p>Username: %s</p>"
            "<p>Email: %s</p>"
            "<p>Last 4 of SSN: %s</p>"
            "</body></html>";

    char *response = malloc(strlen(page) + strlen(session->username) + strlen(session->email) + strlen(session->ssn_last_four));
    sprintf(response, page, session->username, session->email, session->ssn_last_four);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free_session_data(session);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}