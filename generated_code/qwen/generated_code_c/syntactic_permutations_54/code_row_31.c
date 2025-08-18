#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body> \
              <form method=\"POST\" action=\"/do_login\"> \
              Username: <input type=\"text\" name=\"username\"><br> \
              Password: <input type=\"password\" name=\"password\"><br> \
              <input type=\"submit\" value=\"Login\"> \
              </form></body></html>"

#define ADMIN_PAGE "<html><body>Welcome to the admin page!</body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char *page = PAGE;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") == 0) {
        if (*upload_data_size != 0) {
            char username[100], password[100];
            sscanf(upload_data, "username=%99[^&]&password=%99s", username, password);

            // Example check for username and password
            if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
                const char *redir = "/admin_page";
                struct MHD_Response *response;

                response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
                MHD_add_response_header(response, "Location", redir);
                MHD_queue_response(connection, MHD_HTTP_FOUND, response);
                MHD_destroy_response(response);

                return MHD_YES;
            } else {
                const char *fail_page = "<html><body>Login failed</body></html>";
                struct MHD_Response *response;

                response = MHD_create_response_from_buffer(strlen(fail_page), (void *) fail_page, MHD_RESPMEM_PERSISTENT);
                MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
                MHD_destroy_response(response);

                return MHD_YES;
            }
        } else {
            *con_cls = connection;
            return MHD_POST_PROCESSING;
        }
    }

    return MHD_NO;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char *page = ADMIN_PAGE;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);

    if (daemon == NULL) {
        return 1;
    }

    MHD_add_route(daemon, "/do_login", MHD_HTTP_METHOD_POST, &do_login_handler, NULL);
    MHD_add_route(daemon, "/admin_page", MHD_HTTP_METHOD_GET, &admin_page_handler, NULL);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}