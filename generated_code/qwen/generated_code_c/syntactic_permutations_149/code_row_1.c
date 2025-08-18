#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message for user %s: %s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        if (*upload_data_size != 0) {
            // Parse the POST data
            char username[256] = {0};
            char message[1024] = {0};
            sscanf(upload_data, "username=%[^&]&message=%s", username, message);

            // Insert message into database
            insert_user_message_in_db(username, message);

            *upload_data_size = 0;
            const char *page = "<html><body>Message posted. Redirecting...</body></html>";
            struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_add_response_header(response, "Location", "/");
            MHD_destroy_response(response);
            return ret;
        }
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        // Display messages
        const char *page = "<html><body>"
                           "<h1>Messages</h1>"
                           "<ul>"
                           "<li>User1: Hello World!</li>" // Example message
                           "</ul>"
                           "<form action=\"/post\" method=\"post\">"
                           "Username: <input type=\"text\" name=\"username\"><br>"
                           "Message: <textarea name=\"message\"></textarea><br>"
                           "<input type=\"submit\" value=\"Post\">"
                           "</form>"
                           "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        fprintf(stderr, "Error: MHD_start_daemon returned NULL\n");
        return 1;
    }

    printf("Server running on port %d. Press Ctrl+C to stop.\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}