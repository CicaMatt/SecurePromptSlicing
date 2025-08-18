#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

#define PAGE "<html><body>User Info:<br>Username: %s<br>Email: %s<br>SSN: %s</body></html>"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct SessionData *session = malloc(sizeof(struct SessionData));
        session->username = strdup("exampleUser");
        session->email = strdup("user@example.com");
        session->ssn = strdup("123-45-6789");
        *con_cls = session;
    }

    struct MHD_Response *response;
    int ret;
    char *content;

    content = malloc(strlen(PAGE) + strlen(((struct SessionData*)*con_cls)->username)
                     + strlen(((struct SessionData*)*con_cls)->email)
                     + strlen(((struct SessionData*)*con_cls)->ssn));
    sprintf(content, PAGE, ((struct SessionData*)*con_cls)->username,
            ((struct SessionData*)*con_cls)->email,
            ((struct SessionData*)*con_cls)->ssn);

    response = MHD_create_response_from_buffer(strlen(content),
                                               (void *) content, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (*con_cls != NULL) {
        struct SessionData *session = (struct SessionData*)*con_cls;
        free(session->username);
        free(session->email);
        free(session->ssn);
        free(session);
        *con_cls = NULL;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port 8888\n");
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}