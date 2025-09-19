#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *admin_username = "admin";
const char *admin_password = "admin";

int login(struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    const char *page =
        "<html><body>"
        "<form method=\"post\" action=\"/do_login\">"
        "Username: <input type=\"text\" name=\"username\"><br>"
        "Password: <input type=\"password\" name=\"password\"><br>"
        "<input type=\"submit\" value=\"Login\">"
        "</form>"
        "</body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login(struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int first_time = 1;
    if (first_time) {
        first_time = 0;
        return MHD_YES;
    }

    char username[256] = "";
    char password[256] = "";
    const char *username_param = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char *password_param = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (username_param) {
        strncpy(username, username_param, sizeof(username)-1);
    }
    if (password_param) {
        strncpy(password, password_param, sizeof(password)-1);
    }

    struct MHD_Response *response;
    int ret;

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        response = MHD_create_response_from_buffer(strlen("Redirecting to admin page..."), (void*)"Redirecting to admin page...", MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        ret = MHD_queue_response(connection, MHD_HTTP_MOVED_PERMANENTLY, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*)"Invalid credentials", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_response(response);

    return ret;
}

int admin_page(struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body><h1>Welcome to the Admin Page</h1></body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login, NULL, MHD_OPTION_NOTIFY_COMPLETED, NULL, NULL,
                              MHD_OPTION_URI_LOG_CALLBACK, (MHD_LoggingCallback) printf, NULL,
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    struct MHD_UrlHandlerEntry handlers[] = {
        {"/", MHD_HTTP_METHOD_GET, &login, NULL},
        {"/do_login", MHD_HTTP_METHOD_POST, &do_login, NULL},
        {"/admin_page", MHD_HTTP_METHOD_GET, &admin_page, NULL},
        {NULL, NULL, NULL, NULL}
    };

    MHD_add_uri_handler(daemon, "/", handlers);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}