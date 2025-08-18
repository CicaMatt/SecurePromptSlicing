#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/login") == 0 && strcmp(method, "GET") == 0) {
        const char *page = "<html><body>"
                           "<form method='post' action='/do_login'>"
                           "Username: <input type='text' name='username'><br>"
                           "Password: <input type='password' name='password'><br>"
                           "<input type='submit' value='Login'>"
                           "</form></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page),
                                                                        (void *) page,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(url, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        char *username = strstr(upload_data, "username=");
        char *password = strstr(upload_data, "password=");
        if (username != NULL && password != NULL) {
            username += strlen("username=");
            password += strlen("password=");
            char *end_of_username = strchr(username, '&');
            if (end_of_username != NULL) *end_of_username = '\0';
            if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
                const char *redirect_response = "<html><head><meta http-equiv='refresh' content='0;url=/admin_page'></head></html>";
                struct MHD_Response *response = MHD_create_response_from_buffer(strlen(redirect_response),
                                                                                (void *) redirect_response,
                                                                                MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                MHD_destroy_response(response);
                return ret;
            }
        }
    } else if (strcmp(url, "/admin_page") == 0 && strcmp(method, "GET") == 0) {
        const char *page = "<html><body>Welcome to the admin page!</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page),
                                                                        (void *) page,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
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