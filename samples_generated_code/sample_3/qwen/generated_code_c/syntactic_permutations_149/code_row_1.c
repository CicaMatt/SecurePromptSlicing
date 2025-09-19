#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct UserMessage {
    char *message;
};

void insert_user_message_in_db(const char *message) {
    // Simulate database insertion
    printf("Inserting message into DB: %s\n", message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") == 0 && strcmp(url, "/post") == 0) {
        if (*upload_data_size != 0) {
            insert_user_message_in_db(upload_data);
            *upload_data_size = 0;
            return MHD_queue_response(connection, MHD_HTTP_SEE_OTHER,
                                      MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT));
        } else {
            return MHD_NO;
        }
    } else if (strcmp(url, "/") == 0) {
        const char *response = "<html><body>"
                               "<form action='/post' method='POST'>"
                               "Message: <input type='text' name='message'><br>"
                               "<input type='submit' value='Submit'>"
                               "</form></body></html>";
        int response_length = strlen(response);
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_length, (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    } else {
        return MHD_NO;
    }
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