#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct User {
    const char *username;
    const char *ssn_last_four;
};

struct User user = {"exampleUser", "1234"};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Last 4 of SSN: %s</p>"
                       "</body></html>";
    char buffer[512];
    snprintf(buffer, sizeof(buffer), page, user.username, user.ssn_last_four);

    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(buffer),
                                                (void *)buffer,
                                                MHD_RESPMEM_MUST_COPY);
    if (!response)
        return MHD_NO;

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

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}