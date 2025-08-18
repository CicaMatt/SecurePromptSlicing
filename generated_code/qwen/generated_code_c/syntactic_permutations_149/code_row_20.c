#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *name, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: Name=%s, Message=%s\n", name, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        static int post_processed = 0;
        if (!post_processed) {
            post_processed = 1;
            const char* name = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "name");
            const char* message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");
            insert_user_message_in_db(name, message);
            struct MHD_Response *response = MHD_create_response_from_buffer(
                strlen("<html><body>Redirecting...</body></html>"),
                (void*) "<html><body>Redirecting...</body></html>",
                MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, 302, response);
            MHD_destroy_response(response);
            return ret;
        } else {
            post_processed = 0;
        }
    }

    if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        const char *html_content =
            "<html><body>"
            "<h1>Messages</h1>"
            "<p>Display messages here.</p>"
            "<form action=\"/post\" method=\"post\">"
            "Name: <input type=\"text\" name=\"name\"><br>"
            "Message: <input type=\"text\" name=\"message\"><br>"
            "<input type=\"submit\" value=\"Submit\">"
            "</form></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(
            strlen(html_content),
            (void*) html_content,
            MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, 200, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main(int argc, char *const *argv) {
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