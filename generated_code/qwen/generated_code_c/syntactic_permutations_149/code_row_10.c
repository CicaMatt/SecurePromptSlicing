#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message into database: %s\n", message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, MHD_HTTP_METHOD_POST) == 0) {
        if (*con_cls == NULL) {
            *con_cls = malloc(*upload_data_size + 1);
            memcpy(*con_cls, upload_data, *upload_data_size);
            ((char *)*con_cls)[*upload_data_size] = '\0';
            return MHD_YES;
        } else {
            const char *message = (const char *)*con_cls;
            insert_user_message_in_db(message);
            free(*con_cls);
            *con_cls = NULL;
            struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_add_response_header(response, "Location", "/");
            MHD_destroy_response(response);
            return ret;
        }
    } else if (strcmp(url, "/") == 0 && strcmp(method, MHD_HTTP_METHOD_GET) == 0) {
        const char *html = "<html><body>"
                           "<form method=\"post\" action=\"/post\">"
                           "Message: <input type=\"text\" name=\"message\">"
                           "<input type=\"submit\" value=\"Send\">"
                           "</form>"
                           "<h2>Messages:</h2>"
                           "<p>No messages to display yet.</p>" // Here you would fetch and display messages from the database
                           "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(html), (void *)html, MHD_RESPMEM_PERSISTENT);
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

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}