#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int is_moderator(const char* username) {
    // This function should check if the user is a moderator.
    // For demonstration, let's assume "admin" is the only moderator.
    return strcmp(username, "admin") == 0;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* username = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "username");
    if (!username)
        return MHD_NO;

    int moderator_status = is_moderator(username);

    char response[256];
    snprintf(response, sizeof(response), "{\"is_moderator\": %s}", moderator_status ? "true" : "false");

    struct MHD_Response *response_handle;
    response_handle = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_handle);
    MHD_destroy_response(response_handle);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for Enter key to stop the server

    MHD_stop_daemon(daemon);

    return 0;
}