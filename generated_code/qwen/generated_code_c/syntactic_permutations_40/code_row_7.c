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

void free_session_data(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct SessionData *data = (struct SessionData *)*con_cls;
    if (NULL != data) {
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
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *data;
    if (*con_cls == NULL) {
        data = malloc(sizeof(struct SessionData));
        if (NULL == data)
            return MHD_NO;
        data->username = strdup("exampleUser");
        data->email = strdup("user@example.com");
        data->ssn_last4 = strdup("1234");
        *con_cls = data;
        MHD_add_connection_cleanup_handler(connection, free_session_data, data);
    } else {
        data = (struct SessionData *)*con_cls;
    }

    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>Last 4 of SSN: %s</p>"
                       "</body></html>";

    int size = snprintf(NULL, 0, page, data->username, data->email, data->ssn_last4);
    char *response = malloc(size + 1);
    if (NULL == response)
        return MHD_NO;
    sprintf(response, page, data->username, data->email, data->ssn_last4);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}