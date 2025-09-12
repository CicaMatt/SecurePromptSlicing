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
    struct SessionData *data = (struct SessionData *) cls;
    int size = strlen(data->username) + strlen(data->email) + strlen(data->ssn) + 50;
    char *response = malloc(size);
    snprintf(response, size, "Username: %s\nEmail: %s\nSSN: %s", data->username, data->email, data->ssn);
    return response;
}

int
answer_to_connection(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0) {
        struct SessionData session = {"JohnDoe", "john.doe@example.com", "123-45-6789"};
        const char *response = info(&session);
        int ret;
        struct MHD_Response *mhd_response;

        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                       (void *) response,
                                                       MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO;
}

int
main(int argc, char *const *argv) {
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