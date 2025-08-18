#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct User {
    char username[50];
    char password[50];
};

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>"
                       "<form action=\"/do_login\" method=\"post\">"
                       "Username: <input type=\"text\" name=\"username\"><br>"
                       "Password: <input type=\"password\" name=\"password\"><br>"
                       "<input type=\"submit\" value=\"Login\">"
                       "</form></body></html>";
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
    static int first = 1;
    if (first) {
        first = 0;
        return MHD_YES;
    }

    struct User user = {"admin", "password"};
    char username[50] = {0};
    char password[50] = {0};

    const char *username_param = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char *password_param = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (username_param && password_param) {
        strncpy(username, username_param, sizeof(username) - 1);
        strncpy(password, password_param, sizeof(password) - 1);
    }

    struct MHD_Response *response;
    int ret;

    if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
        const char *redirect_url = "/admin_page";
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", redirect_url);
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        const char *page = "<html><body>Invalid username or password</body></html>";
        response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_response(response);

    return ret;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>Welcome to the Admin Page</body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
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

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}