#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *ptr;

    if (0 != strcmp(method, "POST"))
        return MHD_NO; // Unexpected method

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (0 != *upload_data_size)
        return MHD_NO; // Upload data not fully received

    const char *username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char *message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");

    if (username && message) {
        insert_user_message_in_db(username, message);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen("<html><body>Message posted! <a href=\"/\">Go back</a></body></html>"),
                                                                         (void*) "<html><body>Message posted! <a href=\"/\">Go back</a></body></html>",
                                                                         MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    const char *page =
            "<html><body>"
            "<form method='post' action='/post'>"
            "Username: <input type='text' name='username'><br>"
            "Message: <textarea name='message'></textarea><br>"
            "<input type='submit' value='Post Message'>"
            "</form></body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page),
                                                                     (void*) page,
                                                                     MHD_RESPMEM_PERSISTENT);
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
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}