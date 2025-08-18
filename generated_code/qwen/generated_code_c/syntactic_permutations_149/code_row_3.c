#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message for %s: %s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        static int post_processed = 0;
        if (!post_processed) {
            post_processed = 1;
            const char *data = upload_data;
            char username[256], message[256];
            sscanf(data, "username=%[^&]&message=%s", username, message);
            insert_user_message_in_db(username, message);
            return MHD_redirect_to_url(connection, "/");
        } else {
            post_processed = 0;
        }
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        const char *page = "<html><body>"
                           "<form action=\"/post\" method=\"post\">"
                           "Username: <input type=\"text\" name=\"username\"><br>"
                           "Message: <textarea name=\"message\"></textarea><br>"
                           "<input type=\"submit\" value=\"Submit\">"
                           "</form>"
                           "<h2>Messages:</h2>"
                           "<p>Here messages will be displayed</p>"
                           "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page),
                                                                        (void *) page,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}