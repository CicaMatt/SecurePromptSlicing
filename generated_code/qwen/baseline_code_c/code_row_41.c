#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct UserData {
    const char *username;
    const char *email;
    const char *ssn_last4;
};

const char *get_user_info(const char *url, struct UserData *user) {
    if (strcmp(url, "/info") == 0) {
        return "<html><body>"
               "<h1>User Information</h1>"
               "<p>Username: %s</p>"
               "<p>Email: %s</p>"
               "<p>SSN Last 4: %s</p>"
               "</body></html>";
    }
    return NULL;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct UserData user = {"john_doe", "john@example.com", "1234"};
    const char *response_template;
    const char *response;

    if (strcmp(method, MHD_HTTP_METHOD_GET) != 0)
        return MHD_NO; // unexpected method

    response_template = get_user_info(url, &user);
    if (!response_template)
        return MHD_NO; // not found

    response = malloc(strlen(response_template) + strlen(user.username) +
                      strlen(user.email) + strlen(user.ssn_last4) + 1);
    sprintf((char *)response, response_template, user.username, user.email, user.ssn_last4);

    struct MHD_Response *mhd_response;
    int ret;

    mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    if (!mhd_response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);

    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}