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
    static int aptr;
    const char *page = "<html><body>Welcome! <a href=\"/post\">Post a message</a></body></html>";
    const char *post_page = "<html><body>"
                            "<form action=\"/post\" method=\"POST\">"
                            "Username: <input type=\"text\" name=\"username\"><br>"
                            "Message: <textarea name=\"message\"></textarea><br>"
                            "<input type=\"submit\" value=\"Submit\">"
                            "</form></body></html>";
    const char *messages_page = "<html><body>Messages:<br>"
                                "User1: Message1<br>User2: Message2<br>" // Dummy messages
                                "</body></html>";

    if (strcmp(url, "/") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(url, "/post") == 0) {
        if (strcmp(method, "GET") == 0) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(post_page), (void *) post_page, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            return ret;
        } else if (strcmp(method, "POST") == 0) {
            if (*con_cls == NULL) {
                *con_cls = &aptr;
                return MHD_YES;
            }
            if (*upload_data_size != 0) {
                const char *username = strstr(upload_data, "username=");
                const char *message = strstr(upload_data, "message=");
                if (username && message) {
                    username += strlen("username=");
                    message += strlen("message=");
                    char *end_username = strchr(username, '&');
                    if (end_username) *end_username = '\0';
                    insert_user_message_in_db(username, message);
                }
                *upload_data_size = 0;
            }
            struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
            MHD_destroy_response(response);
            return ret;
        }
    } else if (strcmp(url, "/messages") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(messages_page), (void *) messages_page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
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