#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>Login</h1>"
                       "<form method='POST' action='/do_login'>"
                       "Username: <input type='text' name='username'><br>"
                       "Password: <input type='password' name='password'><br>"
                       "<input type='submit' value='Login'>"
                       "</form></body></html>";
    return send_page(connection, page);
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    const char *data = upload_data + aptr;
    size_t data_len = *upload_data_size - aptr;

    if (*upload_data_size != 0) {
        printf("Received: %.*s\n", (int)data_len, data);
        aptr += data_len;
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char *response_page = "<html><body><h1>Login Successful</h1></body></html>";
    return send_page(connection, response_page);
}

int index_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>Welcome to the Index Page</h1></body></html>";
    return send_page(connection, page);
}

int user_page_handler(void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>User Page</h1></body></html>";
    return send_page(connection, page);
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>Admin Page</h1></body></html>";
    return send_page(connection, page);
}

int send_page(struct MHD_Connection *connection, const char *page) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &index_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    MHD_add_route(daemon, "/login", &MHD_HTTP_METHOD_GET, &login_handler, NULL);
    MHD_add_route(daemon, "/do_login", &MHD_HTTP_METHOD_POST, &do_login_handler, NULL);
    MHD_add_route(daemon, "/", &MHD_HTTP_METHOD_GET, &index_handler, NULL);
    MHD_add_route(daemon, "/user_page", &MHD_HTTP_METHOD_GET, &user_page_handler, NULL);
    MHD_add_route(daemon, "/admin_page", &MHD_HTTP_METHOD_GET, &admin_page_handler, NULL);

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}