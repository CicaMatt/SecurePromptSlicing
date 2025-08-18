#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct SessionData {
    char *email;
    char *ssn_last_four;
};

void free_session_data(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    struct SessionData *sd = (struct SessionData *) cls;
    free(sd->email);
    free(sd->ssn_last_four);
    free(sd);
}

int info_handler(void *cls, struct MHD_Connection *connection,
                const char *url, const char *method,
                const char *version, const char *upload_data,
                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *sd = malloc(sizeof(struct SessionData));
    sd->email = strdup("user@example.com");
    sd->ssn_last_four = strdup("1234");

    const char *response_template =
        "<html><body>"
        "<h1>User Information</h1>"
        "<p>Email: %s</p>"
        "<p>SSN Last 4: %s</p>"
        "</body></html>";

    size_t response_size = snprintf(NULL, 0, response_template, sd->email, sd->ssn_last_four);
    char *response = malloc(response_size + 1);
    snprintf(response, response_size + 1, response_template, sd->email, sd->ssn_last_four);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(response_size, (void *) response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    MHD_add_connection_value(connection, MHD_COOKIE_KIND, "session", (const char *) sd, MHD_COOKIE_FlagsNone, 0);
    MHD_add_response_header(response_obj, "Content-Type", "text/html");

    MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started at port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}