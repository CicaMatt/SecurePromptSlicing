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
    (void)kind; (void)key; (void)value;
    struct SessionData *session = cls;
    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn) free(session->ssn);
    free(session);
}

int info(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
         const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    char response[1024];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s\n",
             session->username ? session->username : "unknown",
             session->email ? session->email : "unknown",
             session->ssn ? session->ssn : "unknown");

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct SessionData *session = malloc(sizeof(struct SessionData));
    session->username = strdup("john_doe");
    session->email = strdup("john.doe@example.com");
    session->ssn = strdup("123-45-6789");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &info, (void*)session,
                                                 MHD_OPTION_NOTIFY_COMPLETED, free_session_data, session,
                                                 MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}