#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function for demonstration purposes
    printf("Inserting message from %s: %s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *response = "<html><body>Welcome! <a href=\"/post\">Post a message</a></body></html>";
    struct MHD_Response *mhd_response;

    if (0 != strcmp(method, "POST") && 0 != strcmp(url, "/post")) {
        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                        (void*) response,
                                                        MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    }

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        char username[128] = {0};
        char message[512] = {0};
        sscanf(upload_data, "username=%[^&]&message=%s", username, message);
        insert_user_message_in_db(username, message);

        *con_cls = NULL;
        *upload_data_size = 0;

        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                        (void*) response,
                                                        MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, mhd_response);
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}