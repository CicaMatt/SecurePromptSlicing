#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    int last_four_digits;
};

int handle_info(struct MHD_Connection *connection, void **con_cls) {
    struct SessionData *session_data = (struct SessionData *)*con_cls;

    if (!session_data || !session_data->username || !session_data->email) {
        const char *response = "Session data not found.";
        return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND,
                                  MHD_create_response_from_buffer(strlen(response), 
                                                                  (void*)response, 
                                                                  MHD_RESPMEM_PERSISTENT));
    }

    char response[256];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits: %04d</p>"
             "</body></html>",
             session_data->username, session_data->email, session_data->last_four_digits);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), 
                                                                        (void*)response, 
                                                                        MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    session_data->username = strdup("exampleUser");
    session_data->email = strdup("user@example.com");
    session_data->last_four_digits = 1234;
    *con_cls = session_data;

    if (strcmp(url, "/info") == 0)
        return handle_info(connection, con_cls);

    const char *not_found_response = "Not found.";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found_response), 
                                                                    (void*)not_found_response, 
                                                                    MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                       void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL == con_cls || NULL == *con_cls)
        return;

    struct SessionData *session_data = (struct SessionData *)*con_cls;
    free(session_data->username);
    free(session_data->email);
    free(session_data);

    *con_cls = NULL;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}