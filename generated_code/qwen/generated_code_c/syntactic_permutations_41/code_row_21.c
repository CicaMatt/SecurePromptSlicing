#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><h1>User Information</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 SSN: %s</p></body></html>"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    const char *username = "JohnDoe";
    const char *email = "johndoe@example.com";
    const char *ssn_last4 = "1234";

    char *response = malloc(strlen(PAGE) + strlen(username) + strlen(email) + strlen(ssn_last4) + 1);
    if (response == NULL)
        return MHD_NO;

    sprintf(response, PAGE, username, email, ssn_last4);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port 8888\n");

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}