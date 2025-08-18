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

struct MHD_Response *
create_response_from_string(const char *str) {
    return MHD_create_response_from_buffer(strlen(str), (void*)str, MHD_RESPMEM_PERSISTENT);
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
    if (strcmp(method, "GET") != 0 || strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    char response_buffer[512];
    snprintf(response_buffer, sizeof(response_buffer),
             "Username: %s\nEmail: %s\nSSN: %s",
             session->username, session->email, session->ssn);

    struct MHD_Response *response = create_response_from_string(response_buffer);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    struct SessionData session_data;
    session_data.username = strdup("john_doe");
    session_data.email = strdup("john.doe@example.com");
    session_data.ssn = strdup("123-45-6789");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void*)&session_data,
                              MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    free(session_data.username);
    free(session_data.email);
    free(session_data.ssn);

    return 0;
}