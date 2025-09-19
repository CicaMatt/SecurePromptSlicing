#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *email;
    char *ssn;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/info") == 0) {
        struct SessionData *session = (struct SessionData *)cls;
        char *response;
        int responseSize;
        responseSize = asprintf(&response, "{\"email\": \"%s\", \"ssn\": \"%s\"}", session->email, session->ssn);
        if (responseSize < 0)
            return MHD_NO;

        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(responseSize, (void *)response, MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;
    struct SessionData session;

    // Example data
    session.email = strdup("user@example.com");
    session.ssn = strdup("123-45-6789");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *)&session,
                              MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    free(session.email);
    free(session.ssn);

    return 0;
}