#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body> \
              <form method='post' action='/do_login'> \
              Username: <input type='text' name='username'><br> \
              Password: <input type='password' name='password'><br> \
              <input type='submit' value='Login'> \
              </form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char *page = PAGE;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (*con_cls == NULL) {
        *con_cls = connection;
        return MHD_YES;
    }

    int ret;
    struct MHD_Response *response;
    const char *username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char *password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        response = MHD_create_response_from_buffer(strlen("Login successful"), (void*) "Login successful", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Login failed"), (void*) "Login failed", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_response(response);
    *con_cls = NULL;

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              &MHD_destroy_connection, NULL,
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}