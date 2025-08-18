#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message for %s: %s\n", username, message);
    return 0; // Return 0 on success
}

const char *get_messages_from_db() {
    // Dummy function to simulate getting messages from the database
    return "User1: Hello\nUser2: World";
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") == 0 && strcmp(url, "/post") == 0) {
        static int aptr;
        const char* ptr;

        struct MHD_PostProcessor *pp = cls;
        if (!pp) {
            pp = MHD_create_post_processor(connection, 1024, answer_to_connection, connection);
            *con_cls = pp;
            return MHD_YES;
        }
        int ret;
        while (MHD_YES == (ret = MHD_post_process(pp, upload_data, *upload_data_size))) {
            if (*upload_data_size > 0) {
                *upload_data_size = 0;
                return MHD_YES;
            }
        }
        MHD_destroy_post_processor(pp);
        *con_cls = NULL;

        const char *username = MHD_lookup_connection_value(connection, MHD_COOKIE_KIND, "username");
        const char *message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");

        if (username && message) {
            insert_user_message_in_db(username, message);
        }

        struct MHD_Response *response = MHD_create_response_from_buffer(
                strlen("<html><head><title>Redirect</title></head><body>Redirecting...</body></html>"),
                (void*) "<html><head><title>Redirect</title></head><body>Redirecting...</body></html>",
                MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/");
        ret = MHD_queue_response(connection, 302, response);
        MHD_destroy_response(response);

        return ret;
    } else if (strcmp(url, "/") == 0) {
        const char *messages = get_messages_from_db();
        struct MHD_Response *response = MHD_create_response_from_buffer(
                strlen(messages),
                (void*) messages,
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

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}