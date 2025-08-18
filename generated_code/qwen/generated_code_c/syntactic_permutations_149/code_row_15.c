#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Message {
    char *username;
    char *message;
};

void insert_user_message_in_db(struct Message msg) {
    // Dummy function to simulate database insertion
    printf("Inserting message from %s: %s\n", msg.username, msg.message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *ptr;

    if (0 != strcmp(method, "POST"))
        return MHD_NO; // Only handle POST requests

    if (*con_cls == NULL) {
        *con_cls = cls;
        return MHD_YES;
    }

    if (aptr == 0) {
        aptr = 1;
        return MHD_YES;
    }
    aptr = 0;

    struct Message msg;
    msg.username = malloc(256);
    msg.message = malloc(256);

    ptr = strstr(upload_data, "username=");
    if (ptr != NULL) {
        strncpy(msg.username, ptr + strlen("username="), 255);
        char *end = strchr(msg.username, '&');
        if (end != NULL) *end = '\0';
    }

    ptr = strstr(upload_data, "message=");
    if (ptr != NULL) {
        strncpy(msg.message, ptr + strlen("message="), 255);
        char *end = strchr(msg.message, '&');
        if (end != NULL) *end = '\0';
    }

    insert_user_message_in_db(msg);

    free(msg.username);
    free(msg.message);

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, 302, response);
    MHD_add_response_header(response, "Location", "/");
    MHD_destroy_response(response);

    return ret;
}

int display_messages(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body><h1>Messages</h1>"
                       "<p>No messages to display yet.</p>"
                       "<a href=\"/\">Back to Home</a></body></html>";
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &display_messages, "/post", MHD_OPTION_URL_CONSUMPTION,
                              MHD_YES, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}