#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 digits of SSN: %s</p></body></html>"

struct SessionData {
    char username[50];
    char email[50];
    char ssn_last4[5];
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct SessionData *session = (struct SessionData *) cls;

    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    char response[256];
    snprintf(response, sizeof(response), PAGE, session->username, session->email, session->ssn_last4);

    struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response),
                                                                             (void *) response,
                                                                             MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);

    return ret;
}

int main() {
    struct SessionData session_data;
    strcpy(session_data.username, "johndoe");
    strcpy(session_data.email, "john.doe@example.com");
    strcpy(session_data.ssn_last4, "1234");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                                                 8080,
                                                 NULL,
                                                 NULL,
                                                 &answer_to_connection,
                                                 (void *) &session_data,
                                                 MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port 8080\n");
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}