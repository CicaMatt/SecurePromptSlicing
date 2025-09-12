#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    const char *username;
    const char *email;
    const char *ssn_last_four;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = cls;

    const char *response_template =
            "<html><body>"
            "<p>Username: %s</p>"
            "<p>Email: %s</p>"
            "<p>SSN Last Four: %s</p>"
            "</body></html>";

    int response_length = snprintf(NULL, 0, response_template,
                                   session->username,
                                   session->email,
                                   session->ssn_last_four);

    char *response = malloc(response_length + 1);
    snprintf(response, response_length + 1, response_template,
             session->username,
             session->email,
             session->ssn_last_four);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
            strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct SessionData session_data = {
        .username = "exampleUser",
        .email = "user@example.com",
        .ssn_last_four = "1234"
    };

    struct MHD_Daemon *daemon = MHD_start_daemon(
            MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
            &answer_to_connection, (void *)&session_data,
            MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}