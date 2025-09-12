#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct SessionData {
    char *email;
    char *ssn;
};

void free_session_data(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL != *con_cls) {
        struct SessionData *session = *con_cls;
        free(session->email);
        free(session->ssn);
        free(session);
        *con_cls = NULL;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    if (*con_cls == NULL) {
        struct SessionData *session = malloc(sizeof(struct SessionData));
        session->email = strdup("user@example.com"); // Example email
        session->ssn = strdup("123-45-6789");       // Example SSN
        *con_cls = session;
    }

    if (0 != strcmp(url, "/info"))
        return MHD_NO;

    const char *response = "{\"email\": \"%s\", \"ssn\": \"%s\"}";
    struct SessionData *session = *con_cls;
    int response_len = snprintf(NULL, 0, response, session->email, session->ssn);
    char *buffer = malloc(response_len + 1);
    sprintf(buffer, response, session->email, session->ssn);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
            strlen(buffer), (void *) buffer, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              free_session_data, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}