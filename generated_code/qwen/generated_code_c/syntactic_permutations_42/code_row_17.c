#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

#define PORT 8888

const char *
get_info_handler(void *cls, struct MHD_Connection *connection,
                 const char *url, const char *method,
                 const char *version, const char *upload_data,
                 size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return NULL;

    struct SessionData *session = cls;
    if (!session || !session->username || !session->email || !session->ssn)
        return NULL;

    char *response = malloc(256);
    snprintf(response, 256, "Username: %s\nEmail: %s\nSSN: %s\n", session->username, session->email, session->ssn);

    int ret;
    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return NULL;
}

int main() {
    struct MHD_Daemon *daemon;

    struct SessionData session;
    session.username = strdup("exampleUser");
    session.email = strdup("user@example.com");
    session.ssn = strdup("123-45-6789");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &get_info_handler, (void *)&session, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    free(session.username);
    free(session.email);
    free(session.ssn);

    return 0;
}