#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *login_form =
    "<html>"
    "  <head><title>Login</title></head>"
    "  <body>"
    "    <form method='post' action='/do_login'>"
    "      Username: <input type='text' name='username'><br>"
    "      Password: <input type='password' name='password'><br>"
    "      <input type='submit' value='Login'>"
    "    </form>"
    "  </body>"
    "</html>";

const char *admin_page =
    "<html>"
    "  <head><title>Admin Page</title></head>"
    "  <body>"
    "    <h1>Welcome Admin!</h1>"
    "  </body>"
    "</html>";

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(login_form),
                                               (void*)login_form, MHD_RESPMEM_PERSISTENT);
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

    if (*upload_data_size != 0) {
        char username[16] = {0};
        char password[16] = {0};

        sscanf(upload_data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            struct MHD_Response *response;
            const char *redirect_url = "/admin_page";
            response = MHD_create_response(0);
            MHD_add_response_header(response, "Location", redirect_url);
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_destroy_response(response);
            return ret;
        }

        *upload_data_size = 0; // Reset for next POST
    }
    return MHD_NO;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(admin_page),
                                               (void*)admin_page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}