#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 of SSN: %s</p></body></html>"

struct User {
    const char *username;
    const char *email;
    const char *ssn_last_four;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct User user = {"john_doe", "john.doe@example.com", "1234"};
    char response[512];
    snprintf(response, sizeof(response), PAGE, user.username, user.email, user.ssn_last_four);

    int ret;
    struct MHD_Response *mhd_response;

    mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                    (void*)response,
                                                    MHD_RESPMEM_MUST_COPY);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                              NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}