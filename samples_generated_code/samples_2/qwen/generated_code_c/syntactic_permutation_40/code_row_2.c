#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

const char *username = "john_doe";
const char *email = "john.doe@example.com";
const char *ssn_last_four = "1234";

int info(struct MHD_Connection *connection) {
    const char *page = "<html><body>"
                       "<h1>User Information</h1>"
                       "<p>Username: %s</p>"
                       "<p>Email: %s</p>"
                       "<p>SSN (last 4): %s</p>"
                       "</body></html>";
    char response[512];
    snprintf(response, sizeof(response), page, username, email, ssn_last_four);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                        (void*) response,
                                                                        MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0)
        return info(connection);

    return MHD_NO;
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