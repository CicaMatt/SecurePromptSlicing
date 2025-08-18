#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct User {
    char *username;
    char *email;
    char *ssn; // Assume this is the full SSN for simplicity
};

const struct User user = {"john_doe", "john@example.com", "123456789"};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    const char *response = "<html><body>"
                           "<p>Username: %s</p>"
                           "<p>Email: %s</p>"
                           "<p>Last 4 digits of SSN: %.4s</p>"
                           "</body></html>";

    if (strcmp(url, "/info") == 0) {
        char buffer[512];
        snprintf(buffer, sizeof(buffer), response, user.username, user.email, user.ssn + strlen(user.ssn) - 4);
        
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(buffer),
                                                                            (void *)buffer,
                                                                            MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO; // URL not found
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT,
                              NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}