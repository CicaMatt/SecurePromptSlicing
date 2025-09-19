#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

void insert_user_message_in_db(const char *message) {
    // Dummy function to simulate inserting a message into a database
    printf("Inserting message into DB: %s\n", message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        if (*upload_data_size != 0) {
            insert_user_message_in_db(upload_data);
            *upload_data_size = 0;
            return MHD_queue_response(connection, MHD_HTTP_FOUND,
                                      MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT));
        } else {
            return MHD_NO;
        }
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        const char *html = "<html><body>"
                           "<h1>Messages</h1>"
                           "<p>Message 1</p>"
                           "<p>Message 2</p>"
                           "<form action=\"/post\" method=\"post\">"
                           "<input type=\"text\" name=\"message\" />"
                           "<input type=\"submit\" value=\"Post Message\" />"
                           "</form>"
                           "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(html), (void*)html, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else {
        return MHD_NO;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}