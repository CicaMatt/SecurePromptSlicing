#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct UserMessage {
    char *username;
    char *message;
};

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulated function to insert message into a database
    printf("Inserting message from %s: %s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        static int post_processed = 0;
        struct MHD_PostProcessor *pp;

        if (!post_processed) {
            post_processed = 1;
            pp = MHD_create_post_processor(connection, 1024, answer_to_connection, connection);
            *con_cls = pp;
            return MHD_YES;
        }

        const char *key, *filename, *content_type, *transfer_encoding;
        size_t off;

        while (MHD_get_post_data(connection, &upload_data, upload_data_size)) {
            int more = MHD_post_process(pp, upload_data, *upload_data_size);
            if (!more) {
                MHD_destroy_post_processor(pp);
                post_processed = 0;
                return MHD_NO;
            }
        }

        pp = (struct MHD_PostProcessor*)*con_cls;

        const char *username = NULL;
        const char *message = NULL;

        while ((MHD_get_post_data(connection, &upload_data, upload_data_size) > 0)) {
            if (!MHD_post_process(pp, upload_data, *upload_data_size))
                break;

            MHD_post_process(pp, NULL, 0);
            key = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
            message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");

            if (key && message) {
                username = key;
                break;
            }
        }

        if (username && message) {
            insert_user_message_in_db(username, message);
        }

        *con_cls = NULL;

        const char *redirect_url = "/";
        struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_add_response_header(response, "Location", redirect_url);
        MHD_destroy_response(response);

        return ret;
    } else if (strcmp(url, "/") == 0) {
        const char *page = "<html><body>"
                           "<form action=\"/post\" method=\"post\">"
                           "Username: <input type=\"text\" name=\"username\"><br>"
                           "Message: <textarea name=\"message\"></textarea><br>"
                           "<input type=\"submit\" value=\"Submit\">"
                           "</form>"
                           "<h2>Messages:</h2>"
                           "<p>No messages yet.</p>"
                           "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
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