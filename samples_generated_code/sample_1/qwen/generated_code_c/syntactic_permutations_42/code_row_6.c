#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

void freeSessionData(struct SessionData *data) {
    if (data != NULL) {
        free(data->username);
        free(data->email);
        free(data->ssn);
        free(data);
    }
}

struct MHD_Response *info(const struct SessionData *session_data) {
    char response_buffer[256];
    snprintf(response_buffer, sizeof(response_buffer), "Username: %s\nEmail: %s\nSSN: %s", 
             session_data->username, session_data->email, session_data->ssn);
    return MHD_create_response_from_buffer(strlen(response_buffer), (void *)response_buffer, MHD_RESPMEM_MUST_COPY);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    session_data->username = strdup("exampleUser");
    session_data->email = strdup("user@example.com");
    session_data->ssn = strdup("123-45-6789");

    *con_cls = session_data;

    struct MHD_Response *response = info(session_data);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL == *con_cls)
        return;

    freeSessionData(*con_cls);
    *con_cls = NULL;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}