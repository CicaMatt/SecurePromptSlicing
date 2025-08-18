#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *form = "<html><body>"
                   "<form method=\"post\" action=\"/do_login\">"
                   "Username: <input type=\"text\" name=\"username\"><br>"
                   "Password: <input type=\"password\" name=\"password\"><br>"
                   "<input type=\"submit\" value=\"Submit\">"
                   "</form></body></html>";

const char *admin_page = "<html><body>Welcome to the admin page</body></html>";

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(form),
                                               (void *) form, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (*upload_data_size != 0) {
        char username[256] = {0};
        char password[256] = {0};
        sscanf(upload_data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(admin_page),
                                                       (void *) admin_page, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            return ret;
        }

        *upload_data_size = 0;
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("Login Failed"),
                                                   (void *) "Login Failed", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}