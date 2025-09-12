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

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    struct SessionData *session = (struct SessionData *)*con_cls;
    if (session != NULL) {
        free(session->username);
        free(session->email);
        free(session->ssn);
        free(session);
        *con_cls = NULL;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = (struct SessionData *)*con_cls;
    if (!session) {
        session = malloc(sizeof(struct SessionData));
        if (!session)
            return MHD_NO;

        session->username = strdup("exampleUsername");
        session->email = strdup("user@example.com");
        session->ssn = strdup("123-45-6789");

        *con_cls = session;
    }

    char response[512];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
             session->username, session->email, session->ssn);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                        (void *)response,
                                                                        MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              free_session_data, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}