#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

typedef struct {
    char *email;
    char *ssn;
} Session;

Session current_session = { .email = "user@example.com", .ssn = "123-45-6789" };

const char *info(void **cls, struct MHD_Connection *connection,
                 const char *url, const char *method,
                 const char *version, const char *upload_data,
                 size_t *upload_data_size, void **ptr) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/info") == 0) {
        const char *response = 
            "<html><body>"
            "<h1>User Information</h1>"
            "<p>Email: %s</p>"
            "<p>SSN: %s</p>"
            "</body></html>";

        int ret = MHD_create_response_from_buffer(
            strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT,
            NULL, 0);

        struct MHD_Response *mhd_response = (struct MHD_Response *)ret;
        if (NULL == mhd_response) return NULL;

        MHD_add_response_header(mhd_response, "Content-Type", 
                                "text/html; charset=UTF-8");

        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret ? MHD_YES : MHD_NO;
    }
    return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for Enter key to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}
