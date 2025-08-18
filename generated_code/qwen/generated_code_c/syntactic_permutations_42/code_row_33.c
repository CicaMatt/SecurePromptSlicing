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
    if (NULL != session) {
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
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (NULL == *con_cls) {
        struct SessionData *session = malloc(sizeof(struct SessionData));
        session->username = strdup("exampleUser");
        session->email = strdup("user@example.com");
        session->ssn = strdup("123-45-6789");
        MHD_add_connection_close_notifier(connection, free_session_data, session);
        *con_cls = session;
    }

    struct SessionData *session = (struct SessionData *)*con_cls;

    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s\n", 
             session->username, session->email, session->ssn);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), 
                                                                          (void *)response, 
                                                                          MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}