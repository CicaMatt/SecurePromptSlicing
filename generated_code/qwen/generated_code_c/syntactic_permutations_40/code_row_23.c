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
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0) {
        struct SessionData *session = cls;
        char response[512];
        snprintf(response, sizeof(response), PAGE, session->username, session->email, session->ssn_last4);

        int ret;
        struct MHD_Response *mhd_response;
        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                       (void*)response,
                                                       MHD_RESPMEM_MUST_COPY);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO;
}

int main() {
    struct SessionData session;
    strcpy(session.username, "johndoe");
    strcpy(session.email, "john.doe@example.com");
    strcpy(session.ssn_last4, "1234");

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                              NULL, NULL,
                              &answer_to_connection, (void*)&session,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}