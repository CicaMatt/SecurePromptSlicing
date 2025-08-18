#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        if (*upload_data_size != 0) {
            char *username = strstr(upload_data, "username=");
            char *message = strstr(upload_data, "&message=");

            if (username && message) {
                username += strlen("username=");
                message += strlen("&message=");

                // Null-terminate the strings
                char *end_username = strchr(username, '&');
                if (end_username) *end_username = '\0';

                char *end_message = strchr(message, '&');
                if (end_message) *end_message = '\0';

                insert_user_message_in_db(username, message);

                const char *response = "<html><body>Message posted successfully. <a href=\"/messages\">View messages</a></body></html>";
                struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
                MHD_destroy_response(mhd_response);
                return ret;
            }
        } else {
            // Expecting POST data
            *con_cls = connection;
            return MHD_YES;
        }
    }

    const char *not_found = "<html><body>Not found</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found), (void *) not_found, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}