#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct UserData {
    const char *username;
    const char *email;
    const char *ssn_last4;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct UserData *userData = cls;
    char response[512];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             userData->username, userData->email, userData->ssn_last4);

    struct MHD_Response *response_obj;
    int ret;

    response_obj = MHD_create_response_from_buffer(strlen(response),
                                                   (void *)response,
                                                   MHD_RESPMEM_MUST_COPY);
    if (!response_obj)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main(int argc, char **argv) {
    struct UserData userData = {"JohnDoe", "john.doe@example.com", "1234"};
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, &userData, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}