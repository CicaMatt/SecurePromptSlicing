#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0 || strcmp(url, "/post") != 0) {
        return MHD_NO;
    }

    const char *username = NULL;
    const char *message = NULL;

    struct MHD_PostProcessor *pp = MHD_create_post_processor(connection, 1024,
                                                            &answer_iterator, NULL);
    if (NULL == pp)
        return MHD_NO;

    int ret = MHD_YES;
    while (MHD_POSTPROCESSOR_CONTINUE == MHD_post_process(pp, upload_data, *upload_data_size)) {
        if (*upload_data_size) {
            *upload_data_size = 0;
        } else {
            break;
        }
    }

    MHD_destroy_post_processor(pp);

    insert_user_message_in_db(username, message);

    struct MHD_Response *response = MHD_create_response(302);
    MHD_add_response_header(response, "Location", "/");
    ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    MHD_destroy_response(response);

    return ret;
}

int answer_iterator(void *con_cls, enum MHD_ValueKind kind,
                    const char *key, const char *filename, const char *content_type,
                    const char *transfer_encoding, const char *data, uint64_t off, size_t size) {
    if (0 == strcmp(key, "username")) {
        // Copy the username data
    } else if (0 == strcmp(key, "message")) {
        // Copy the message data
    }
    return MHD_YES;
}

int main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}