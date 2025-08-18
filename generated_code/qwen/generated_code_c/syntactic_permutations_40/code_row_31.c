#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last4;
};

struct MHD_Connection *current_connection;

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    struct SessionData *session = (struct SessionData *)*con_cls;
    if (session != NULL) {
        free(session->username);
        free(session->email);
        free(session->ssn_last4);
        free(session);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = (struct SessionData *)*con_cls;
    if (session == NULL) {
        session = malloc(sizeof(struct SessionData));
        session->username = strdup("john_doe");
        session->email = strdup("john.doe@example.com");
        session->ssn_last4 = strdup("1234");
        *con_cls = session;
        MHD_add_connection_context(connection, (void *)current_connection, free_session_data);
    }

    char response[512];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN Last 4: %s",
             session->username, session->email, session->ssn_last4);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                        (void *)response,
                                                                        MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}