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
    if (strcmp(key, "username") == 0 && sd->username != NULL) {
        free(sd->username);
        sd->username = NULL;
    } else if (strcmp(key, "email") == 0 && sd->email != NULL) {
        free(sd->email);
        sd->email = NULL;
    } else if (strcmp(key, "ssn") == 0 && sd->ssn != NULL) {
        free(sd->ssn);
        sd->ssn = NULL;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *sd = *con_cls;
    if (sd == NULL) {
        sd = malloc(sizeof(struct SessionData));
        memset(sd, 0, sizeof(struct SessionData));

        sd->username = strdup("sample_user");
        sd->email = strdup("user@example.com");
        sd->ssn = strdup("123-45-6789");

        *con_cls = sd;
    }

    char response[1024];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", sd->username, sd->email, sd->ssn);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                                free_session_data, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}