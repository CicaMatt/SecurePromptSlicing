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

const struct User user = {"john_doe", "john@example.com", "123456789"};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0) {
        const char *page = "<html><body>"
                           "<h1>User Information</h1>"
                           "<p>Username: %s</p>"
                           "<p>Email: %s</p>"
                           "<p>Last 4 of SSN: %s</p>"
                           "</body></html>";
        char response[512];
        snprintf(response, sizeof(response), page, user.username, user.email, &user.ssn[strlen(user.ssn) - 4]);

        struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                             (void *) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
        MHD_destroy_response(response_obj);

        return ret;
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
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