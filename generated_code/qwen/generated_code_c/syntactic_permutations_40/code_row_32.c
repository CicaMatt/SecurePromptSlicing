#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *email;
    char *ssn_last4;
};

void free_session_data(void *cls) {
    struct SessionData *sd = cls;
    if (sd) {
        free(sd->email);
        free(sd->ssn_last4);
        free(sd);
    }
}

int info_handler(void *cls, struct MHD_Connection *connection,
                 const char *url, const char *method,
                 const char *version, const char *upload_data,
                 size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *sd = *con_cls;
    if (!sd)
        return MHD_NO;

    const char *response_template =
            "<html><body>"
            "<p>Email: %s</p>"
            "<p>Last 4 digits of SSN: %s</p>"
            "</body></html>";
    size_t response_size = snprintf(NULL, 0, response_template, sd->email, sd->ssn_last4) + 1;
    char *response = malloc(response_size);
    snprintf(response, response_size, response_template, sd->email, sd->ssn_last4);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    // Create a session
    struct SessionData *sd = malloc(sizeof(struct SessionData));
    sd->email = strdup("user@example.com");
    sd->ssn_last4 = strdup("1234");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info_handler, sd, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, sd,
                              MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}