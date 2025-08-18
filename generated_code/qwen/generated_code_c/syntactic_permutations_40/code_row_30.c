#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *email;
    char *ssn_last_four;
};

void free_session_data(void *cls) {
    struct SessionData *data = (struct SessionData *) cls;
    if (data) {
        free(data->email);
        free(data->ssn_last_four);
        free(data);
    }
}

int info_handler(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *data = (struct SessionData *) cls;
    if (!data || !data->email || !data->ssn_last_four)
        return MHD_NO;

    char response[256];
    snprintf(response, sizeof(response), "Email: %s\nSSN Last 4: %s", data->email, data->ssn_last_four);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                          (void *) response,
                                                                          MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    return ret;
}

int main() {
    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    if (!session_data)
        return 1;

    session_data->email = strdup("user@example.com");
    session_data->ssn_last_four = strdup("1234");

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info_handler, (void *) session_data,
                              MHD_OPTION_NOTIFY_COMPLETED, free_session_data,
                              NULL, MHD_OPTION_END);

    if (!daemon) {
        free_session_data(session_data);
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    free_session_data(session_data);
    return 0;
}