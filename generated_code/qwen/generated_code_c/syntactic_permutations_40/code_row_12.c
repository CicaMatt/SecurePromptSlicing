#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last_four;
};

void free_session_data(void *cls) {
    struct SessionData *data = (struct SessionData *) cls;
    free(data->username);
    free(data->email);
    free(data->ssn_last_four);
    free(data);
}

int info_handler(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *data = (struct SessionData *) cls;
    if (!data)
        return MHD_NO;

    const char *page_template =
            "<html><body>"
            "<h1>User Information</h1>"
            "<p>Username: %s</p>"
            "<p>Email: %s</p>"
            "<p>Last 4 digits of SSN: %s</p>"
            "</body></html>";

    char *page = malloc(strlen(page_template) + strlen(data->username) + strlen(data->email) + strlen(data->ssn_last_four));
    if (!page)
        return MHD_NO;

    sprintf(page, page_template, data->username, data->email, data->ssn_last_four);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct SessionData *data = malloc(sizeof(struct SessionData));
    if (!data)
        return 1;

    data->username = strdup("exampleUser");
    data->email = strdup("user@example.com");
    data->ssn_last_four = strdup("1234");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &info_handler, (void *) data, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, data,
                                                 MHD_OPTION_END);
    if (!daemon) {
        free_session_data(data);
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}