#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last4;
};

void free_session_data(void *cls) {
    struct SessionData *data = (struct SessionData *) cls;
    free(data->username);
    free(data->email);
    free(data->ssn_last4);
    free(data);
}

int info_handler(void *cls, struct MHD_Connection *connection,
                 const char *url, const char *method,
                 const char *version, const char *upload_data,
                 size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session_data = (struct SessionData *) cls;
    if (!session_data)
        return MHD_NO;

    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>SSN Last 4 Digits: %s</p>"
                       "</body></html>";

    char response[512];
    snprintf(response, sizeof(response), page,
             session_data->username, session_data->email, session_data->ssn_last4);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    session_data->username = strdup("john_doe");
    session_data->email = strdup("john.doe@example.com");
    session_data->ssn_last4 = strdup("1234");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &info_handler, (void *) session_data,
                                                 MHD_OPTION_NOTIFY_COMPLETED, free_session_data, NULL,
                                                 MHD_OPTION_END);
    if (!daemon) {
        free_session_data(session_data);
        return 1;
    }

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}