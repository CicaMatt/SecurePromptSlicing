#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PAGE "<html><body>Username: %s<br>Email: %s<br>Last 4 digits of SSN: %s</body></html>"

struct SessionData {
    char username[50];
    char email[50];
    char ssn_last_4[5];
};

int info(struct MHD_Connection *connection, struct SessionData *session) {
    char buffer[200];
    snprintf(buffer, sizeof(buffer), PAGE, session->username, session->email, session->ssn_last_4);

    int ret;
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int handler(void *cls, struct MHD_Connection *connection, const char *url,
            const char *method, const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    struct SessionData *session;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    session = malloc(sizeof(struct SessionData));
    if (!session)
        return MHD_NO;

    strcpy(session->username, "john_doe");
    strcpy(session->email, "john.doe@example.com");
    strcpy(session->ssn_last_4, "1234");

    *con_cls = session;
    int ret = info(connection, session);
    free(session);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}