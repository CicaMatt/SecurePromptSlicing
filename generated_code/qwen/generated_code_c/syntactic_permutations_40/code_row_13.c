#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last_4;
};

void free_session_data(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL != *con_cls) {
        struct SessionData *data = (struct SessionData *)*con_cls;
        free(data->username);
        free(data->email);
        free(data->ssn_last_4);
        free(data);
        *con_cls = NULL;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct SessionData *data = malloc(sizeof(struct SessionData));
        data->username = strdup("exampleUser");
        data->email = strdup("user@example.com");
        data->ssn_last_4 = strdup("1234");
        *con_cls = (void *)data;
    }

    const char *response_page = "<html><body>"
                                "<h1>User Information</h1>"
                                "<p>Username: %s</p>"
                                "<p>Email: %s</p>"
                                "<p>Last 4 digits of SSN: %s</p>"
                                "</body></html>";

    struct SessionData *data = (struct SessionData *)*con_cls;
    char response[512];
    snprintf(response, sizeof(response), response_page, data->username, data->email, data->ssn_last_4);

    int ret;
    struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response),
                                                                          (void *)strdup(response),
                                                                          MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}