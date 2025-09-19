#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    const char *username;
    const char *email;
    const char *ssn;
};

const char *
info(struct MHD_Connection *connection, struct SessionData *session) {
    if (NULL == session || NULL == session->username || NULL == session->email || NULL == session->ssn) {
        return "Session data not found";
    }
    char *response = malloc(1024);
    snprintf(response, 1023, "Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
    return response;
}

int
answer_to_connection(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET"))
        return MHD_NO;
    if (0 != strcmp(url, "/info"))
        return MHD_NO;

    struct SessionData session = {"john_doe", "john@example.com", "123-45-6789"};
    const char *response = info(connection, &session);

    int ret;
    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_MUST_FREE);
    if (!mhd_response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int
main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}