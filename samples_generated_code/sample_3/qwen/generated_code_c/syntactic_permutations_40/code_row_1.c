#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>Username: %s<br>Email: %s<br>Last 4 of SSN: %s</body></html>"

struct SessionData {
    char username[50];
    char email[100];
    char ssn_last4[5];
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const struct SessionData *session_data = (struct SessionData *) cls;

    if (0 != strcmp(method, "GET"))
        return MHD_NO;              /* unexpected method */
    if (&aptr != *con_cls)
    {
        /* do never respond on first call */
        *con_cls = &aptr;
        return MHD_YES;
    }
    if (0 == strcmp(url, "/info")) {
        char buffer[512];
        snprintf(buffer, sizeof(buffer), PAGE, session_data->username, session_data->email, session_data->ssn_last4);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer),
                                                                        (void*) buffer,
                                                                        MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;                  /* unexpected URL */
}

int main() {
    struct SessionData session_data;
    strcpy(session_data.username, "john_doe");
    strcpy(session_data.email, "john.doe@example.com");
    strcpy(session_data.ssn_last4, "1234");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                                                 NULL, NULL,
                                                 &answer_to_connection, (void *) &session_data,
                                                 MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}