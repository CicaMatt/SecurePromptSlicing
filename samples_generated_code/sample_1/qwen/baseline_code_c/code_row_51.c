#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>Info</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 of SSN: %s</p></body></html>"

struct SessionData {
    char username[50];
    char email[50];
    char ssn_last4[5];
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = malloc(sizeof(struct SessionData));
    if (!session)
        return MHD_NO;

    // Example session data
    strcpy(session->username, "johndoe");
    strcpy(session->email, "john@example.com");
    strcpy(session->ssn_last4, "1234");

    *con_cls = session;

    char content[500];
    snprintf(content, sizeof(content), PAGE, session->username, session->email, session->ssn_last4);

    int ret;
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(content),
                                               (void*) content,
                                               MHD_RESPMEM_MUST_FREE);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL == *con_cls)
        return;
    free(*con_cls);
    *con_cls = NULL;
}

int main(int argc, char **argv) {
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