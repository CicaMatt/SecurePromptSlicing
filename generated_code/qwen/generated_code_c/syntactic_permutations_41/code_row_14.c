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

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    const struct UserData *user_data = (struct UserData *)cls;
    char response[512];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 of SSN: %s</p>"
             "</body></html>",
             user_data->username, user_data->email, user_data->ssn_last4);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), 
                                                                          (void *)response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    return ret;
}

int main() {
    struct UserData user_data = {"john_doe", "john@example.com", "1234"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *)&user_data,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}