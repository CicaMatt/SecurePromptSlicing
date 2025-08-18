#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function for demonstration purposes
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        char buf[512];
        const char *username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
        const char *message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");

        if (username && message) {
            insert_user_message_in_db(username, message);
            snprintf(buf, sizeof(buf), "<html><head><meta http-equiv='refresh' content='0;url=/'></head><body></body></html>");
        } else {
            snprintf(buf, sizeof(buf), "Invalid request");
        }

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buf), (void *) buf, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        char *html_content = "<html><body>"
                             "<form method='post' action='/post'>"
                             "Username: <input type='text' name='username'><br>"
                             "Message: <input type='text' name='message'><br>"
                             "<input type='submit' value='Submit'>"
                             "</form></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(html_content), (void *) html_content, MHD_RESPMEM_PERSISTENT);
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

    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}