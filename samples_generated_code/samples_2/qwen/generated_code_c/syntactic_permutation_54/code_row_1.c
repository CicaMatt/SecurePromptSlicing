#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *form = "<html><body>"
                   "<form method=\"post\" action=\"/do_login\">"
                   "Username: <input type=\"text\" name=\"username\"><br>"
                   "Password: <input type=\"password\" name=\"password\"><br>"
                   "<input type=\"submit\" value=\"Login\">"
                   "</form></body></html>";

const char *admin_page = "<html><body>Admin Page</body></html>";

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0) {
        int ret;
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(form), (void *)form, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int first_time = 1;
    if (first_time) {
        first_time = 0;
        return MHD_YES;
    }
    if (*upload_data_size != 0) {
        // Simple parsing for demonstration purposes
        const char *username_start = strstr(upload_data, "username=");
        const char *password_start = strstr(upload_data, "password=");
        if (username_start && password_start) {
            username_start += strlen("username=");
            password_start += strlen("password=");
            size_t username_len = strchr(username_start, '&') - username_start;
            size_t password_len = strchr(password_start, '&') - password_start;

            char username[100];
            char password[100];
            strncpy(username, username_start, username_len);
            username[username_len] = '\0';
            strncpy(password, password_start, password_len);
            password[password_len] = '\0';

            if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
                struct MHD_Response *response = MHD_create_response_from_buffer(strlen(admin_page), (void *)admin_page, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                MHD_destroy_response(response);
                return ret;
            }
        }

        *upload_data_size = 0;
    }
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(form), (void *)form, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_ARRAY, (const union MHD_OptionItem[]) {
                                  {MHD_OPTION_URI_LOG_CALLBACK, NULL, &do_login_handler},
                                  {MHD_OPTION_END}
                              }, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}