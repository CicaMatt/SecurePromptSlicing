#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function for demonstration purposes
    printf("Inserting message from %s: %s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        const char *username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
        const char *message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");

        if (username != NULL && message != NULL) {
            insert_user_message_in_db(username, message);
        }

        struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_add_response_header(response, "Location", "/");
        MHD_destroy_response(response);

        return ret;
    }

    const char *page = "<html><body>Hello, world!</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}