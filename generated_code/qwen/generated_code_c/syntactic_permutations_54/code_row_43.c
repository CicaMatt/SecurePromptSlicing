#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = 
        "<html><body>"
        "<form method=\"post\" action=\"/do_login\">"
        "Username: <input type=\"text\" name=\"username\"><br>"
        "Password: <input type=\"password\" name=\"password\"><br>"
        "<input type=\"submit\" value=\"Login\">"
        "</form></body></html>";

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
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

    static int first_call = 1;
    if (first_call) {
        first_call = 0;
        return MHD_YES;
    }
    first_call = 1;

    char username[256];
    char password[256];
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));

    int ret = sscanf(upload_data, "username=%[^&]&password=%s", username, password);
    if (ret != 2)
        return MHD_NO;

    struct MHD_Response *response;
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        response = MHD_create_response_from_buffer(strlen("Redirecting..."), (void*)"Redirecting...", MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Login Failed"), (void*)"Login Failed", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_FORBIDDEN, response);
    }
    MHD_destroy_response(response);

    return ret;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>Welcome to the Admin Page</h1></body></html>";

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED, NULL,
                              NULL, MHD_OPTION_URI_LOG_CALLBACK, NULL, NULL,
                              MHD_OPTION_ADD_INTERNAL_ROUTE, "/do_login", &MHD_HTTP_METHOD_POST, &do_login_handler, NULL,
                              MHD_OPTION_ADD_INTERNAL_ROUTE, "/admin_page", &MHD_HTTP_METHOD_GET, &admin_page_handler, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}