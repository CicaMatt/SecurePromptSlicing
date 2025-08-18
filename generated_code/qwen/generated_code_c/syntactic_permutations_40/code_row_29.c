#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct SessionData {
    char *username;
    char *email;
    char *ssn_last4;
};

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    struct SessionData *session = (struct SessionData *)*con_cls;
    if (session) {
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
    if (strcmp(url, "/info") != 0 || strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData **session = (struct SessionData **)con_cls;
    if (*session == NULL) {
        *session = malloc(sizeof(struct SessionData));
        if (*session == NULL)
            return MHD_NO;
        (*session)->username = strdup("exampleUser");
        (*session)->email = strdup("user@example.com");
        (*session)->ssn_last4 = strdup("1234");

        struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        if (MHD_queue_response(connection, MHD_HTTP_OK, response) != MHD_YES) {
            MHD_destroy_response(response);
            return MHD_NO;
        }
        MHD_add_connection_close_callback(connection, free_session_data, session);
        MHD_destroy_response(response);
        return MHD_YES;
    }

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Email: %s\nLast 4 of SSN: %s\n", (*session)->email, (*session)->ssn_last4);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}