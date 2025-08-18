#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct User {
    const char *username;
    const char *email;
    const char *ssn_last_four;
};

const struct User user = {"JohnDoe", "johndoe@example.com", "1234"};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    const char *response = 
        "<html><body>"
        "<h1>User Information</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 of SSN: %s</p>"
        "</body></html>";

    char buffer[512];
    snprintf(buffer, sizeof(buffer), response, user.username, user.email, user.ssn_last_four);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(buffer),
                                                                          (void *)buffer,
                                                                          MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) 
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for key press to exit

    MHD_stop_daemon(daemon);
    return 0;
}