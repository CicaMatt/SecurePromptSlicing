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
    struct SessionData *sd = (struct SessionData *) cls;
    if (strcmp(key, "username") == 0) {
        free(sd->username);
    } else if (strcmp(key, "email") == 0) {
        free(sd->email);
    } else if (strcmp(key, "ssn") == 0) {
        free(sd->ssn);
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

    struct SessionData *sd = (struct SessionData *) malloc(sizeof(struct SessionData));
    sd->username = strdup("example_username");
    sd->email = strdup("user@example.com");
    sd->ssn = strdup("123-45-6789");

    char response[512];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", sd->username, sd->email, sd->ssn);

    struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response),
                                                                             (void *) response,
                                                                             MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);

    MHD_remove_connection_value(connection, MHD_COOKIE_KIND, "username");
    MHD_remove_connection_value(connection, MHD_COOKIE_KIND, "email");
    MHD_remove_connection_value(connection, MHD_COOKIE_KIND, "ssn");

    free_session_data(sd, MHD_COOKIE_KIND, "username", sd->username);
    free_session_data(sd, MHD_COOKIE_KIND, "email", sd->email);
    free_session_data(sd, MHD_COOKIE_KIND, "ssn", sd->ssn);

    free(sd);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}