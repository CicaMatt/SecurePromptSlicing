#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 digits of SSN: %s</p></body></html>"

struct SessionData {
    char username[50];
    char email[50];
    char ssn_last_four[5];
};

void *create_session(const char *username, const char *email, const char *ssn) {
    struct SessionData *session = malloc(sizeof(struct SessionData));
    strncpy(session->username, username, sizeof(session->username) - 1);
    strncpy(session->email, email, sizeof(session->email) - 1);
    strncpy(session->ssn_last_four, ssn + strlen(ssn) - 4, sizeof(session->ssn_last_four) - 1);
    return session;
}

void free_session(void *cls) {
    struct SessionData *session = (struct SessionData *) cls;
    free(session);
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

    char response[512];
    snprintf(response, sizeof(response), PAGE, session->username, session->email, session->ssn_last_four);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                      (void *) response,
                                                                      MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct SessionData *session = create_session("john_doe", "john@example.com", "123-45-6789");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                                                NULL, NULL, &info_handler,
                                                session, MHD_OPTION_NOTIFY_COMPLETED, free_session,
                                                NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server started on port 8888\n");
    getchar();

    MHD_stop_daemon(daemon);
    free_session(session);

    return 0;
}