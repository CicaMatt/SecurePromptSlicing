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
answer_to_connection(void *cls,
                     struct MHD_Connection *connection,
                     const char *url,
                     const char *method,
                     const char *version,
                     const char *upload_data,
                     size_t *upload_data_size,
                     void **con_cls) {
    static int aptr;
    const char *page = NULL;
    struct MHD_Response *response;
    int ret;

    if (0 != strcmp(method, "GET"))
        return NULL;

    if (&aptr != *con_cls) {
        /* do never respond on first call */
        *con_cls = &aptr;
        return MHD_YES;
    }

    *con_cls = NULL; /* reset when done */

    struct SessionData *session_data = (struct SessionData *) cls;

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Username: %s<br>Email: %s<br>SSN: %s",
             session_data->username,
             session_data->email,
             session_data->ssn);

    page = strdup(buffer);
    response = MHD_create_response_from_buffer(strlen(page),
                                                (void *) page,
                                                MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret == MHD_YES ? page : NULL;
}

int main() {
    struct MHD_Daemon *daemon;
    struct SessionData session_data;

    session_data.username = "exampleUser";
    session_data.email = "user@example.com";
    session_data.ssn = "123-45-6789";

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) &session_data,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); /* keep server running */

    MHD_stop_daemon(daemon);
    return 0;
}