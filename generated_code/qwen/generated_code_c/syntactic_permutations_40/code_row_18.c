#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last_four;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session_data = cls;
    char response[512];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session_data->username, session_data->email, session_data->ssn_last_four);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct SessionData session_data;
    session_data.username = strdup("johndoe");
    session_data.email = strdup("john.doe@example.com");
    session_data.ssn_last_four = strdup("1234");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                  &answer_to_connection, (void *) &session_data,
                                                  MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    free(session_data.username);
    free(session_data.email);
    free(session_data.ssn_last_four);

    return 0;
}