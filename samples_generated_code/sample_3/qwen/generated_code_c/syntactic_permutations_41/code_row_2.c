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

const char *get_user_info(struct UserData *data) {
    static char response[256];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 of SSN: %s</p>"
             "</body></html>",
             data->username, data->email, data->ssn_last4);
    return response;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0) {
        struct UserData user = {"JohnDoe", "john.doe@example.com", "1234"};
        const char *response = get_user_info(&user);

        int ret;
        struct MHD_Response *mhd_response;
        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                        (void *) response,
                                                        MHD_RESPMEM_PERSISTENT);
        if (!mhd_response)
            return MHD_NO;

        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO;
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