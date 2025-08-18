#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

void *create_session_data(const char *username, const char *email, const char *ssn) {
    struct SessionData *data = malloc(sizeof(struct SessionData));
    data->username = strdup(username);
    data->email = strdup(email);
    data->ssn = strdup(ssn);
    return data;
}

void destroy_session_data(void *cls) {
    struct SessionData *data = (struct SessionData *) cls;
    free(data->username);
    free(data->email);
    free(data->ssn);
    free(data);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *data = cls;
    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s\n", data->username, data->email, data->ssn);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    return ret;
}

int main() {
    struct SessionData *session_data = create_session_data("john_doe", "john@example.com", "123-45-6789");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT,
                                                 NULL, NULL,
                                                 &answer_to_connection, session_data,
                                                 MHD_OPTION_NOTIFY_COMPLETED, destroy_session_data,
                                                 NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    destroy_session_data(session_data);

    return 0;
}