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

const struct UserInfo user_info = {
    .username = "johndoe",
    .email = "john.doe@example.com",
    .ssn_last4 = "1234"
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    const char *response = "<html><body>"
                           "<p>Username: %s</p>"
                           "<p>Email: %s</p>"
                           "<p>SSN Last 4: %s</p>"
                           "</body></html>";

    char *final_response;
    if (asprintf(&final_response, response, user_info.username, user_info.email, user_info.ssn_last4) < 0)
        return MHD_NO;

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(final_response),
                                                                         (void *) final_response,
                                                                         MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

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