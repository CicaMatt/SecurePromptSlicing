#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *user_info = "<html><body>"
                        "<h1>User Information</h1>"
                        "<p>Username: john_doe</p>"
                        "<p>Email: john.doe@example.com</p>"
                        "<p>Social Security Number: 123-45-6789</p>"
                        "</body></html>";

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(user_info),
                                                                     (void *) user_info,
                                                                     MHD_RESPMEM_PERSISTENT);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}