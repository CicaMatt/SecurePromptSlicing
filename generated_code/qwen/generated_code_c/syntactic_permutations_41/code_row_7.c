#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct User {
    const char *username;
    const char *email;
    const char *ssn;
};

const struct User user = {"john_doe", "john.doe@example.com", "123456789"};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>"
                      "<h1>User Information</h1>"
                      "<p>Username: %s</p>"
                      "<p>Email: %s</p>"
                      "<p>Last 4 digits of SSN: %.*s</p>"
                      "</body></html>";
    const char *last_four_ssn = user.ssn + strlen(user.ssn) - 4;
    int ret;
    struct MHD_Response *response;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    response = MHD_create_response_from_buffer_asp(
            asprintf(&page, page, user.username, user.email, 4, last_four_ssn),
            (void*) page,
            MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}