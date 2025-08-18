#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    const char *email;
    const char *ssn;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                              const char *url, const char *method,
                              const char *version, const char *upload_data,
                              size_t *upload_data_size, void **con_cls) {
    static int first = 1;

    if (first) {
        first = 0;
        return MHD_YES;
    }

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    const char *response = NULL;
    size_t response_size = 0;

    if (strcmp(url, "/info") == 0) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "Email: %s\nSSN: %s", session->email, session->ssn);
        response = buffer;
        response_size = strlen(response);
    } else {
        return MHD_NO;
    }

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct SessionData session = {"example@example.com", "123-45-6789"};
    
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                &answer_to_connection, &session, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}