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
    static int aptr;
    const char *ptr;

    if (NULL == *con_cls) {
        *con_cls = cls;
        return MHD_YES;
    }

    if (0 != strcmp(method, "POST"))
        return send_page(connection, "<html><body>Only POST allowed.</body></html>");

    ptr = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    if (!ptr)
        return send_page(connection, "<html><body>Username not provided.</body></html>");
    const char *username = ptr;

    ptr = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");
    if (!ptr)
        return send_page(connection, "<html><body>Message not provided.</body></html>");
    const char *message = ptr;

    insert_user_message_in_db(username, message);

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen("<html><body>Redirecting...</body></html>"),
                                                (void*) "<html><body>Redirecting...</body></html>",
                                                MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, 302, response);
    MHD_add_response_header(response, "Location", "/");
    MHD_destroy_response(response);

    return ret;
}

int send_page(struct MHD_Connection *connection, const char *page) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for user input

    MHD_stop_daemon(daemon);
    return 0;
}