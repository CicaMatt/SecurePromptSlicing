#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct UserSession {
    char *username;
    char *email;
    char *ssn;
};

void free_user_session(struct UserSession *session) {
    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn) free(session->ssn);
    free(session);
}

struct MHD_Response* generate_info_response(struct UserSession *session) {
    char response_buffer[256];
    snprintf(response_buffer, sizeof(response_buffer), "Username: %s\nEmail: %s\nSSN: %s",
             session->username ? session->username : "Not Set",
             session->email ? session->email : "Not Set",
             session->ssn ? session->ssn : "Not Set");
    return MHD_create_response_from_buffer(strlen(response_buffer), (void*)response_buffer, MHD_RESPMEM_PERSISTENT);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct UserSession *session = malloc(sizeof(struct UserSession));
        session->username = strdup("exampleUser");
        session->email = strdup("user@example.com");
        session->ssn = strdup("123-45-6789"); // In a real application, never handle SSN this way
        *con_cls = session;
        return MHD_YES;
    }

    struct UserSession *session = (struct UserSession*)*con_cls;

    if (strcmp(url, "/info") == 0) {
        struct MHD_Response *response = generate_info_response(session);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (*con_cls) {
        free_user_session((struct UserSession*)*con_cls);
        *con_cls = NULL;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}