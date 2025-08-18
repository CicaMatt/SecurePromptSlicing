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

void free_session_data(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct SessionData *data = (struct SessionData *)*con_cls;
    if (NULL != data) {
        free(data->username);
        free(data->email);
        free(data->ssn);
        free(data);
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

    struct SessionData *data = malloc(sizeof(struct SessionData));
    data->username = strdup("exampleUser");
    data->email = strdup("user@example.com");
    data->ssn = strdup("123-45-6789");

    *con_cls = data;
    MHD_add_response_header(connection, "Content-Type", "text/plain");

    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s\n",
             data->username, data->email, data->ssn);

    struct MHD_Response *response_object = MHD_create_response_from_buffer(
        strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_session_data,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}