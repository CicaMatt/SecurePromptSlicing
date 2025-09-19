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

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    struct SessionData *data = (struct SessionData *)*con_cls;
    if (data != NULL) {
        free(data->username);
        free(data->email);
        free(data->ssn);
        free(data);
        *con_cls = NULL;
    }
}

int info(struct MHD_Connection *connection, void **con_cls) {
    struct SessionData *session_data = (struct SessionData *)*con_cls;

    if (session_data == NULL) {
        return MHD_NO;
    }

    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", session_data->username, session_data->email, session_data->ssn);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    session_data->username = strdup("exampleUser");
    session_data->email = strdup("user@example.com");
    session_data->ssn = strdup("123-45-6789");

    *con_cls = session_data;
    MHD_add_connection_cleanup_handler(connection, free_session_data, con_cls);

    return info(connection, con_cls);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}