#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *username = "john_doe";
const char *email = "john.doe@example.com";
const char *ssn_last_four = "1234";

int info(struct MHD_Connection *connection) {
    const char *page = "<html><body>"
                        "<h1>User Information</h1>"
                        "<p>Username: %s</p>"
                        "<p>Email: %s</p>"
                        "<p>SSN Last 4: %s</p>"
                        "</body></html>";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), page, username, email, ssn_last_four);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer), (void*)buffer, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") == 0 && strcmp(method, "GET") == 0) {
        return info(connection);
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}