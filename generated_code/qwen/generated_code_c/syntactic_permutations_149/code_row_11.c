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
    if (strcmp(url, "/post") == 0 && strcmp(method, MHD_HTTP_METHOD_POST) == 0) {
        static int aptr;
        const char* username = NULL;
        const char* message = NULL;

        if (*upload_data_size != 0) {
            username = strstr(upload_data, "username=");
            if (username != NULL) {
                username += strlen("username=");
                char *end = strchr(username, '&');
                if (end != NULL) *end = '\0';
            }

            message = strstr(upload_data, "message=");
            if (message != NULL) {
                message += strlen("message=");
                char *end = strchr(message, '&');
                if (end != NULL) *end = '\0';
            }

            insert_user_message_in_db(username, message);
            *upload_data_size = 0;

            const char* redirect_url = "<html><head><meta http-equiv=\"refresh\" content=\"0;URL=/\"></head></html>";
            struct MHD_Response *response = MHD_create_response_from_buffer(strlen(redirect_url),
                                                                            (void*)redirect_url, 
                                                                            MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);

            return ret;
        } else {
            if (!aptr) {
                aptr = 1;
                return MHD_YES;
            }
            const char* post_form = "<html><body>"
                                    "<form action=\"/post\" method=\"post\">"
                                    "Username: <input type=\"text\" name=\"username\"><br>"
                                    "Message: <textarea name=\"message\"></textarea><br>"
                                    "<input type=\"submit\" value=\"Post Message\">"
                                    "</form></body></html>";
            struct MHD_Response *response = MHD_create_response_from_buffer(strlen(post_form),
                                                                            (void*)post_form, 
                                                                            MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);

            return ret;
        }
    } else if (strcmp(url, "/") == 0) {
        const char* display_messages_page = "<html><body>"
                                            "<h1>Messages</h1>"
                                            "<p>Here would be the list of messages.</p>"
                                            "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(display_messages_page),
                                                                        (void*)display_messages_page, 
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
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}