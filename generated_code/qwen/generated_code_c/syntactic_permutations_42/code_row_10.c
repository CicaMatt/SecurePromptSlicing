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

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    char response[512];
    snprintf(response, sizeof(response), 
             "{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":\"%s\"}",
             session->username, session->email, session->ssn);

    int ret;
    struct MHD_Response *response_object = MHD_create_response_from_buffer(
        strlen(response),
        (void*) response,
        MHD_RESPMEM_MUST_COPY);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);
    return ret;
}

int main() {
    struct SessionData session = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123-45-6789"
    };

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, 
                                                NULL, NULL,
                                                &answer_to_connection, (void*) &session,
                                                MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}