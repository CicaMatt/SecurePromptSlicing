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
    if (strcmp(key, "session") == 0) {
        free(sd->username);
        free(sd->email);
        free(sd->ssn);
        free(sd);
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

    struct SessionData *sd = malloc(sizeof(struct SessionData));
    sd->username = strdup("exampleUser");
    sd->email = strdup("user@example.com");
    sd->ssn = strdup("123-45-6789");

    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>SSN: %s</p>"
                       "</body></html>";

    char *response_page = malloc(strlen(page) + strlen(sd->username) + strlen(sd->email) + strlen(sd->ssn));
    sprintf(response_page, page, sd->username, sd->email, sd->ssn);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_page),
                                                                     (void *) response_page,
                                                                     MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_add_connection_value(connection, MHD_COOKIE, "session", (const char *) sd, MHD_COOKIE_FLAG_DISCARD);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_session_data,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}