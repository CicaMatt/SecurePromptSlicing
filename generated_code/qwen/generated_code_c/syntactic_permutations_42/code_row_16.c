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
info(void *cls) {
    struct SessionData *data = (struct SessionData *) cls;
    static char response[512];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", data->username, data->email, data->ssn);
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

    if (strcmp(url, "/info") == 0) {
        struct SessionData *data = malloc(sizeof(struct SessionData));
        data->username = strdup("john_doe");
        data->email = strdup("john.doe@example.com");
        data->ssn = strdup("123-45-6789");

        const char *response = info(data);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                     MHD_create_response_from_buffer(strlen(response),
                                                                     (void *) response,
                                                                     MHD_RESPMEM_MUST_FREE));
        free(data->username);
        free(data->email);
        free(data->ssn);
        free(data);
        return ret;
    }

    return MHD_NO;
}

int
main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    printf("Server running on port %d...\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}