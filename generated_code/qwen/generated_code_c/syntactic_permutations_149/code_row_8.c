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
    if (strcmp(method, "POST") == 0 && strcmp(url, "/submit") == 0) {
        static int postprocessed = 0;
        struct MHD_PostProcessor *pp;

        if (!postprocessed) {
            pp = MHD_create_post_processor(connection, 1024, answer_to_connection, con_cls);
            if (pp == NULL)
                return MHD_NO;
            postprocessed = 1;
            *con_cls = pp;
            return MHD_YES;
        }
        const char* username = "";
        const char* message = "";

        while (MHD_post_process(pp, upload_data, *upload_data_size) > 0) {
            if (*upload_data_size != 0) {
                // Handle the post data here
                printf("Received: %.*s\n", (int)*upload_data_size, upload_data);
                // For simplicity, assume the format is "username=example&message=hello"
                const char* prefix_username = "username=";
                const char* prefix_message = "message=";
                if (strncmp(upload_data, prefix_username, strlen(prefix_username)) == 0) {
                    username = upload_data + strlen(prefix_username);
                } else if (strncmp(upload_data, prefix_message, strlen(prefix_message)) == 0) {
                    message = upload_data + strlen(prefix_message);
                }
            }
        }
        insert_user_message_in_db(username, message);

        MHD_destroy_post_processor(pp);
        *con_cls = NULL;
        return redirect_to_root(connection);
    } else if (strcmp(url, "/") == 0) {
        const char *page = "<html><body>"
                           "<form method='post' action='/submit'>"
                           "Username: <input type='text' name='username'><br>"
                           "Message: <textarea name='message'></textarea><br>"
                           "<input type='submit' value='Submit'>"
                           "</form></body></html>";
        int ret;
        struct MHD_Response *response;

        response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
        if (!response)
            return MHD_NO;
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }
    return MHD_NO;
}

int redirect_to_root(struct MHD_Connection *connection) {
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    if (response == NULL)
        return MHD_NO;

    MHD_add_response_header(response, "Location", "/");
    int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);

    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}