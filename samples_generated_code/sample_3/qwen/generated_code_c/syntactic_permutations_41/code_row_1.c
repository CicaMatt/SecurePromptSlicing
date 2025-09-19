#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Social Security Number: %s</p></body></html>"

struct User {
    const char *username;
    const char *email;
    const char *ssn;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct User user = {"john_doe", "john.doe@example.com", "123-45-6789"};
    char response[1024];
    snprintf(response, sizeof(response), PAGE, user.username, user.email, user.ssn);

    int ret;
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void*)response,
                                                                         MHD_RESPMEM_MUST_COPY);
    if (!mhd_response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);

    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port 8888\n");
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}