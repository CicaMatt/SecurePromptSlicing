#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message for %s: %s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, MHD_HTTP_METHOD_POST) == 0) {
        static int aptr;
        const char* username = NULL;
        const char* message = NULL;

        if (aptr != *upload_data_size) {
            return MHD_YES;
        }
        aptr = *upload_data_size;

        char copy[*upload_data_size + 1];
        memcpy(copy, upload_data, *upload_data_size);
        copy[*upload_data_size] = '\0';

        char* saveptr;
        strtok_r(copy, "&", &saveptr); // Skip username=
        username = strtok_r(NULL, "=", &saveptr);
        message = strtok_r(NULL, "=", &saveptr);

        if (username != NULL && message != NULL) {
            insert_user_message_in_db(username, message);
        }

        const char *response = "<html><body>Message posted. Redirecting...</body></html>";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_add_response_header(mhd_response, "Location", "/");
        MHD_destroy_response(mhd_response);
        return ret;
    } else if (strcmp(url, "/") == 0 && strcmp(method, MHD_HTTP_METHOD_GET) == 0) {
        const char *response = "<html><body>"
                               "<form action=\"/post\" method=\"post\">"
                               "Username: <input type=\"text\" name=\"username\"><br>"
                               "Message: <textarea name=\"message\"></textarea><br>"
                               "<input type=\"submit\" value=\"Post\">"
                               "</form></body></html>";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}