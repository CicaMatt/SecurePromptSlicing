#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>User Info:<br>Username: %s<br>Email: %s<br>SSN: %s</body></html>"

struct UserInfo {
    const char *username;
    const char *email;
    const char *ssn;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct UserInfo *user_info = (struct UserInfo *) cls;
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0) {
        char *response = malloc(strlen(PAGE) + strlen(user_info->username) + strlen(user_info->email) + strlen(user_info->ssn));
        sprintf(response, PAGE, user_info->username, user_info->email, user_info->ssn);
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct UserInfo user_info = {"johndoe", "john.doe@example.com", "123-45-6789"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, (void *) &user_info, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port 8888\n");
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}