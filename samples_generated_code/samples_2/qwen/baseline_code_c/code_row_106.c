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

void free_session_data(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    struct SessionData *data = (struct SessionData *) cls;
    if (data != NULL) {
        free(data->username);
        free(data->email);
        free(data->ssn_last_four);
        free(data);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method, const char *version,
                         const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0 || strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *data = malloc(sizeof(struct SessionData));
    data->username = strdup("john_doe");
    data->email = strdup("john@example.com");
    data->ssn_last_four = strdup("1234");

    const char *response_page = "<html><body>"
                                "<h1>Info</h1>"
                                "<p>Username: %s</p>"
                                "<p>Email: %s</p>"
                                "<p>SSN Last 4: %s</p>"
                                "</body></html>";
    size_t response_size = snprintf(NULL, 0, response_page, data->username, data->email, data->ssn_last_four);
    char *response = malloc(response_size + 1);
    sprintf(response, response_page, data->username, data->email, data->ssn_last_four);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);

    MHD_destroy_response(mhd_response);
    MHD_add_connection_close_callback(connection, free_session_data, data);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d...\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}