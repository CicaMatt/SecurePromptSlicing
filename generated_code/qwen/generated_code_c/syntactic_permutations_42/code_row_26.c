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

void free_session_data(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    struct SessionData *session = (struct SessionData *) cls;
    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn) free(session->ssn);
    free(session);
}

const char *info(struct MHD_Connection *connection, struct SessionData *session_data) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", session_data->username, session_data->email, session_data->ssn);
    return response;
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

    const char *response_content = info(connection, session_data);
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_content),
                                                                     (void *) response_content,
                                                                     MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    MHD_add_connection_cleanup_handler(connection, free_session_data, session_data);

    return ret;
}

int main(int argc, char **argv) {
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