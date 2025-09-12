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
    struct SessionData *data = (struct SessionData *) cls;
    if (data->username) free(data->username);
    if (data->email) free(data->email);
    if (data->ssn) free(data->ssn);
}

const char *info(struct MHD_Connection *connection) {
    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    session_data->username = strdup("exampleUser");
    session_data->email = strdup("user@example.com");
    session_data->ssn = strdup("123-45-6789");

    char *response;
    asprintf(&response, "Username: %s\nEmail: %s\nSSN: %s", 
             session_data->username, session_data->email, session_data->ssn);

    MHD_add_response_header(connection, "Content-Type", "text/plain");
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);

    free_session_data(session_data, MHD_COOKIE_KIND, "session", NULL);
    MHD_destroy_response(mhd_response);

    return ret == MHD_YES ? "OK" : "ERROR";
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method, 
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, MHD_HTTP_METHOD_GET) == 0 && strcmp(url, "/info") == 0) {
        return info(connection) == "OK" ? MHD_YES : MHD_NO;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                  &answer_to_connection, NULL, 
                                                  MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}