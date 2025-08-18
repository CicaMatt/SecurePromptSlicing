#include <stdio.h>
#include <stdlib.h>
#include "microhttpd.h"

#define PORT 8080

struct Session {
    char *username;
    char *email;
    char *ssn;
};

static int info(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    struct Session *session = cls;
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
             session->username, session->email, session->ssn);

    struct MHD_Response *res = MHD_create_response_from_buffer(strlen(response),
                                                                (void *)response,
                                                                MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, res);
    MHD_destroy_response(res);
    return ret;
}

static void *request_completed(void *cls, struct MHD_Connection *connection,
                               void **con_cls, enum MHD_RequestTerminationCode toe) {
    free(cls);
    return NULL;
}

int main() {
    struct Session *session = malloc(sizeof(struct Session));
    session->username = "user123";
    session->email = "user123@example.com";
    session->ssn = "123-45-6789";

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD,
                                                 PORT, NULL, NULL,
                                                 &info, session,
                                                 MHD_OPTION_NOTIFY_COMPLETED,
                                                 request_completed, NULL,
                                                 MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    free(session);
    return 0;
}