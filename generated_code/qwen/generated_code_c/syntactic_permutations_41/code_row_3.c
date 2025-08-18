#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct User {
    const char *username;
    const char *email;
    const char *ssn_last_4;
};

const struct User user = {"john_doe", "john@example.com", "1234"};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>Last 4 of SSN: %s</p>"
                       "</body></html>";

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    char *response = malloc(strlen(page) + strlen(user.username) + strlen(user.email) + strlen(user.ssn_last_4));
    sprintf(response, page, user.username, user.email, user.ssn_last_4);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *argv[]) {
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