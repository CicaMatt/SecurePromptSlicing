#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

static int info_handler(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    char *response_str = malloc(256);
    snprintf(response_str, 256, "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}",
             session->username, session->email, session->ssn);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_str),
                                                                     (void*) response_str,
                                                                     MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct SessionData session_data;
    session_data.username = strdup("exampleUser");
    session_data.email = strdup("user@example.com");
    session_data.ssn = strdup("123-45-6789");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT,
                                                 NULL, NULL,
                                                 &info_handler, (void*) &session_data,
                                                 MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    free(session_data.username);
    free(session_data.email);
    free(session_data.ssn);

    return 0;
}