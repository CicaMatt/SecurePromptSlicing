#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "microhttpd.h"

#define PORT 8080

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/submit") == 0 && strcmp(method, "POST") == 0) {
        static int aptr;
        struct MHD_PostProcessor *pp;

        if (*con_cls == NULL) {
            pp = MHD_create_post_processor(connection, 1024, answer_to_connection, &aptr);
            *con_cls = pp;
            return MHD_YES;
        }

        pp = *con_cls;

        const char *key, *filename, *content_type, *transfer_encoding, *data;
        size_t off, size;
        int end;
        end = MHD_post_process(pp, upload_data, *upload_data_size);
        if (!end) {
            return MHD_NO;  // Error occurred
        }
        key = "username";
        filename = content_type = transfer_encoding = NULL;
        data = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, key);
        const char *username = data;

        key = "message";
        data = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, key);
        const char *message = data;

        if (username && message) {
            insert_user_message_in_db(username, message);
        }

        MHD_destroy_post_processor(pp);
        *con_cls = NULL;

        struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, 302, response);
        MHD_add_response_header(response, "Location", "/");
        MHD_destroy_response(response);

        return ret;
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        const char *page = "<html><body>"
                           "<form method='post' action='/submit'>"
                           "Username: <input type='text' name='username'><br>"
                           "Message: <textarea name='message'></textarea><br>"
                           "<input type='submit' value='Submit'>"
                           "</form>"
                           "<h2>Messages:</h2>"
                           "<ul>"
                           // Here you would fetch and display messages from the database
                           "<li>User1: Message1</li>"  // Example message
                           "<li>User2: Message2</li>"  // Example message
                           "</ul>"
                           "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else {
        return MHD_NO;  // URL not found
    }
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for user input to exit
    MHD_stop_daemon(daemon);
    return 0;
}