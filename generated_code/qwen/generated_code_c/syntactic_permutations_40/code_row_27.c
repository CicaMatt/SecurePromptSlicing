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

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    char response[256];
    snprintf(response, sizeof(response), "<html><body>"
                                         "<p>Username: %s</p>"
                                         "<p>Email: %s</p>"
                                         "<p>SSN Last 4: %s</p>"
                                         "</body></html>",
             session->username, session->email, session->ssn_last4);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct SessionData session = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn_last4 = "1234"
    };

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, (void*) &session,
                                                 MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    free(session.username);
    free(session.email);
    free(session.ssn_last4);

    return 0;
}