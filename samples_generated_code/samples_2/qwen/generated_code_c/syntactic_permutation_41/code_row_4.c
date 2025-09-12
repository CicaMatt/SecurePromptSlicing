#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct UserInfo {
    const char *username;
    const char *email;
    const char *ssn_last4;
};

const struct UserInfo user = {"JohnDoe", "john.doe@example.com", "1234"};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") == 0 && strcmp(method, "GET") == 0) {
        const char *page = 
            "<html><body>"
            "<h1>User Information</h1>"
            "<p>Username: %s</p>"
            "<p>Email: %s</p>"
            "<p>Last 4 of SSN: %s</p>"
            "</body></html>";
        char *response;
        int response_length = asprintf(&response, page, user.username, user.email, user.ssn_last4);
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_length,
                                                                          (void *) response,
                                                                          MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }
    return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}