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
    if (data) {
        free(data->username);
        free(data->email);
        free(data->ssn_last4);
        free(data);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *data = (struct SessionData *) cls;
    if (!data)
        return MHD_NO;

    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>Last 4 digits of SSN: %s</p>"
                       "</body></html>";

    char response[512];
    snprintf(response, sizeof(response), page, data->username, data->email, data->ssn_last4);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                          (void*) response,
                                                                          MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    return ret;
}

int main(int argc, char **argv) {
    struct SessionData *data = malloc(sizeof(struct SessionData));
    data->username = strdup("exampleUser");
    data->email = strdup("user@example.com");
    data->ssn_last4 = strdup("1234");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, (void *) data,
                                                 MHD_OPTION_NOTIFY_COMPLETED, free_session_data,
                                                 data,
                                                 MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    free_session_data(data);
    return 0;
}