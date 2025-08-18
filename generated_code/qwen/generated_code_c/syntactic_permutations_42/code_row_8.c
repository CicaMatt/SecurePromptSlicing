#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

const char *
info(void *cls) {
    struct SessionData *session_data = (struct SessionData *) cls;
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", session_data->username, session_data->email, session_data->ssn);
    return response;
}

int
answer_to_connection(void *cls,
                     struct MHD_Connection *connection,
                     const char *url,
                     const char *method,
                     const char *version,
                     const char *upload_data,
                     size_t *upload_data_size,
                     void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData session_data = {
            .username = "john_doe",
            .email = "john@example.com",
            .ssn = "123-45-6789"
    };

    if (strcmp(url, "/info") == 0) {
        const char *page = info(&session_data);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int
main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}