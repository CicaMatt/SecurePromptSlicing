#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 digits of SSN: %s</p></body></html>"

struct SessionData {
    char *username;
    char *email;
    char *ssn_last_four;
};

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    struct SessionData *data = (struct SessionData *)*con_cls;
    if (NULL != data) {
        free(data->username);
        free(data->email);
        free(data->ssn_last_four);
        free(data);
        *con_cls = NULL;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *data = malloc(sizeof(struct SessionData));
    data->username = strdup("example_user");
    data->email = strdup("user@example.com");
    data->ssn_last_four = strdup("1234");

    *con_cls = data;
    MHD_add_response_header(response, "Content-Type", "text/html");
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              free_session_data, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port 8888\n");
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}