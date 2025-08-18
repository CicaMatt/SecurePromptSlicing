#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *login_form = "<html><body>"
                         "<form action=\"/login\" method=\"post\">"
                         "Username: <input type=\"text\" name=\"username\"><br>"
                         "Password: <input type=\"password\" name=\"password\"><br>"
                         "<input type=\"submit\" value=\"Submit\">"
                         "</form></body></html>";

const char *admin_page = "<html><body>Admin Page</body></html>";

int handle_login_form(struct MHD_Connection *connection) {
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(login_form),
                                                (void*) login_form,
                                                MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int handle_login_submission(struct MHD_Connection *connection,
                             const char *username,
                             const char *password) {
    int ret;
    struct MHD_Response *response;

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        response = MHD_create_response_from_buffer(strlen(admin_page),
                                                    (void*) admin_page,
                                                    MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    } else {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_response(response);

    return ret;
}

int answer_to_connection(void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **con_cls) {
    if (strcmp(url, "/login") == 0 && strcmp(method, MHD_HTTP_METHOD_GET) == 0) {
        return handle_login_form(connection);
    } else if (strcmp(url, "/login") == 0 && strcmp(method, MHD_HTTP_METHOD_POST) == 0) {
        const char *username = MHD_lookup_connection_value(connection,
                                                           MHD_POSTDATA_KIND,
                                                           "username");
        const char *password = MHD_lookup_connection_value(connection,
                                                           MHD_POSTDATA_KIND,
                                                           "password");

        if (NULL != username && NULL != password) {
            return handle_login_submission(connection, username, password);
        }
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT,
                              NULL,
                              NULL,
                              &answer_to_connection,
                              NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}