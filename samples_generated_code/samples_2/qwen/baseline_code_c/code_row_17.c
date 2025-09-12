#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8080

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

int info(struct MHD_Connection *connection, void **con_cls) {
    struct SessionData *session = (struct SessionData *)*con_cls;

    if (!session || !session->username || !session->email || !session->ssn) {
        return MHD_NO;
    }

    char *response = malloc(256);
    snprintf(response, 256, "Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);

    int ret = MHD_queue_response(connection,
                                 MHD_HTTP_OK,
                                 MHD_create_response_from_buffer(strlen(response),
                                                                 (void *)response,
                                                                 MHD_RESPMEM_MUST_FREE));
    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") == 0 && strcmp(method, "GET") == 0) {
        struct SessionData *session = malloc(sizeof(struct SessionData));
        session->username = strdup("john_doe");
        session->email = strdup("john@example.com");
        session->ssn = strdup("123-45-6789");
        *con_cls = session;
        return info(connection, con_cls);
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT,
                              NULL,
                              NULL,
                              &answer_to_connection,
                              NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}