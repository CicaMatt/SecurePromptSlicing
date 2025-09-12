#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 SSN: %s</p></body></html>"

struct UserInfo {
    const char *username;
    const char *email;
    const char *ssn_last_four;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct UserInfo *user_info = cls;
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), PAGE, user_info->username, user_info->email, user_info->ssn_last_four);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer),
                                                                    (void*)buffer,
                                                                    MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    struct UserInfo user_info = {"johndoe", "john.doe@example.com", "1234"};

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                              NULL, NULL, &answer_to_connection,
                              (void*)&user_info, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port 8888\n");
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}