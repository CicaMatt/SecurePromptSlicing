#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'><input type='text' name='username' placeholder='Username'/><br><input type='password' name='password' placeholder='Password'/><br><button type='submit'>Login</button></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(PAGE), (void*)PAGE, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int first_time = 1;
    if (first_time) {
        first_time = 0;
        return MHD_YES;
    }

    const char* username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char* password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    int ret;
    struct MHD_Response *response;
    if (username && password && strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        response = MHD_create_response_from_buffer(strlen("<html><body>Redirecting to admin page...</body></html>"), (void*)"<html><body>Redirecting to admin page...</body></html>", MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("<html><body>Login failed</body></html>"), (void*)"<html><body>Login failed</body></html>", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    printf("Server started on port 8080\n");

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &do_login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}