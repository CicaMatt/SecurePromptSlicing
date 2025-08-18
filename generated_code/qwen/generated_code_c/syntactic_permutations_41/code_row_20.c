#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

const char *email = "user@example.com";
const char *ssn_last_four = "1234";

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    const char *response = "<html><body>"
                           "<p>Email: %s</p>"
                           "<p>SSN Last Four: %s</p>"
                           "</body></html>";

    char *page = malloc(strlen(response) + strlen(email) + strlen(ssn_last_four));
    sprintf(page, response, email, ssn_last_four);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
            strlen(page), (void *) page, MHD_RESPMEM_MUST_FREE);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
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