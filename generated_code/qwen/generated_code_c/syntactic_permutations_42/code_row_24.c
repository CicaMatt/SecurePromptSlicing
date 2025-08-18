#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

int info(void *cls, struct MHD_Connection *connection,
         const char *url, const char *method,
         const char *version, const char *upload_data,
         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
             session->username, session->email, session->ssn);

    int ret;
    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                   (void *)response,
                                                   MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;
    struct SessionData session_data;

    session_data.username = "john_doe";
    session_data.email = "john.doe@example.com";
    session_data.ssn = "123-45-6789";

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &info, (void *)&session_data, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}