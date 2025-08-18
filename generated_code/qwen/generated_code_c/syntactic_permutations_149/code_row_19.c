#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct PostData {
    char *username;
    char *message;
};

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message for %s: %s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        struct PostData *data = (struct PostData *)*con_cls;
        if (*con_cls == NULL) {
            data = malloc(sizeof(struct PostData));
            data->username = NULL;
            data->message = NULL;
            *con_cls = data;
            return MHD_YES;
        }
        if (*upload_data_size != 0) {
            char *content = strdup(upload_data);
            char *token = strtok(content, "&");
            while (token != NULL) {
                char *eq = strchr(token, '=');
                if (eq != NULL) {
                    *eq = '\0';
                    if (strcmp(token, "username") == 0) {
                        data->username = strdup(eq + 1);
                    } else if (strcmp(token, "message") == 0) {
                        data->message = strdup(eq + 1);
                    }
                }
                token = strtok(NULL, "&");
            }
            free(content);

            insert_user_message_in_db(data->username, data->message);

            free(data->username);
            free(data->message);
            free(data);
            *con_cls = NULL;

            struct MHD_Response *response = MHD_create_response_from_buffer(
                    strlen("<html><body>Message posted. Redirecting...</body></html>"),
                    (void *)"<html><body>Message posted. Redirecting...</body></html>", 
                    MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, 302, response);
            MHD_add_response_header(response, "Location", "/");
            MHD_destroy_response(response);
            return ret;
        }
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        const char *page = "<html><body>"
                           "<form action=\"/post\" method=\"post\">"
                           "Username: <input type=\"text\" name=\"username\"><br>"
                           "Message: <input type=\"text\" name=\"message\"><br>"
                           "<input type=\"submit\" value=\"Submit\">"
                           "</form>"
                           "<h3>Messages:</h3>"
                           "<p>No messages yet.</p>" // Display messages here
                           "</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(
                strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, 200, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);

    return 0;
}