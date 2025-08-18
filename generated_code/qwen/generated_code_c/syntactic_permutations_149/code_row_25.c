#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        static int aptr;
        const char *data = upload_data;

        if (*con_cls == NULL) {
            *con_cls = &aptr;
            return MHD_YES;
        }

        if (0 != *upload_data_size) {
            char username[128] = "", message[512] = "";
            sscanf(data, "username=%127[^&]&message=%511s", username, message);
            insert_user_message_in_db(username, message);

            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen("<html><head><title>Redirect</title></head><body><a href=\"/\">Go back to home</a></body></html>"),
                                                       (void *) "<html><head><title>Redirect</title></head><body><a href=\"/\">Go back to home</a></body></html>",
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, 302, response);
            MHD_destroy_response(response);
            *upload_data_size = 0;
            return ret;
        }
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("<html><head><title>Home</title></head><body>Welcome to the Home Page!</body></html>"),
                                                   (void *) "<html><head><title>Home</title></head><body>Welcome to the Home Page!</body></html>",
                                                   MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, 200, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);

    return 0;
}