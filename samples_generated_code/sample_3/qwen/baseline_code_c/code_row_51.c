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

void free_session_data(void *cls, struct MHD_Connection *connection,
                       void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL == *con_cls)
        return;
    struct SessionData *session = (struct SessionData *)*con_cls;
    free(session->username);
    free(session->email);
    free(session->ssn_last4);
    free(session);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET"))
        return MHD_NO;
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session;
    if (*con_cls == NULL) {
        session = malloc(sizeof(struct SessionData));
        session->username = strdup("exampleUser");
        session->email = strdup("user@example.com");
        session->ssn_last4 = strdup("1234");
        *con_cls = session;
        MHD_add_response_header(connection, "Content-Type", "text/html");
    } else {
        session = (struct SessionData *)*con_cls;
    }

    char response[500];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>SSN Last 4: %s</p>"
             "</body></html>",
             session->username, session->email, session->ssn_last4);

    struct MHD_Response *response_object;
    int ret;

    response_object = MHD_create_response_from_buffer(strlen(response),
                                                      (void *)response,
                                                      MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              free_session_data, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}