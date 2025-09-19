#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>Info</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 SSN: %s</p></body></html>"

struct UserData {
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

    struct UserData *data = cls;
    char response[512];
    snprintf(response, sizeof(response), PAGE, data->username, data->email, data->ssn_last_four);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void*)response,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct UserData user_data = {"john_doe", "john@example.com", "1234"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, &user_data, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port 8888. Press enter to stop.\n");
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}