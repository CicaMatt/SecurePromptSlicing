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
    if (strcmp(key, "username") == 0) {
        free(session->username);
    } else if (strcmp(key, "email") == 0) {
        free(session->email);
    } else if (strcmp(key, "ssn") == 0) {
        free(session->ssn);
    }
}

int info(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
         const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {

    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup(MHD_lookup_connection_value(connection, MHD_COOKIE_KIND, "username"));
    session->email = strdup(MHD_lookup_connection_value(connection, MHD_COOKIE_KIND, "email"));
    session->ssn = strdup(MHD_lookup_connection_value(connection, MHD_COOKIE_KIND, "ssn"));

    char *response_body;
    asprintf(&response_body, "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}",
             session->username ? session->username : "",
             session->email ? session->email : "",
             session->ssn ? session->ssn : "");

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_body),
                                                                      (void *) response_body,
                                                                      MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn) free(session->ssn);
    free(session);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}