#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>" \
             "<form method=\"post\" action=\"/do_login\">" \
             "Username: <input type=\"text\" name=\"username\"><br>" \
             "Password: <input type=\"password\" name=\"password\"><br>" \
             "<input type=\"submit\" value=\"Submit\">" \
             "</form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

int login(void *cls, struct MHD_Connection *connection,
          const char *url, const char *method,
          const char *version, const char *upload_data,
          size_t *upload_data_size, void **con_cls) {
    const char *page = PAGE;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login(void *cls, struct MHD_Connection *connection,
             const char *url, const char *method,
             const char *version, const char *upload_data,
             size_t *upload_data_size, void **con_cls) {
    static int first = 1;
    const char *username;
    const char *password;

    if (first) {
        first = 0;
        return MHD_YES;
    }

    username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (username && password &&
        strcmp(username, ADMIN_USERNAME) == 0 &&
        strcmp(password, ADMIN_PASSWORD) == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen("<html><body>Access Denied</body></html>"), (void*) "<html><body>Access Denied</body></html>", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login, NULL, MHD_OPTION_NOTIFY_COMPLETED, NULL, NULL,
                              MHD_OPTION_ADD_EXTRA_HEADER, "Connection", "close",
                              MHD_OPTION_ARRAY, (const union MHD_OptionItem[]) {
                                  {MHD_OPTION_METHODS_TO_TRY, 0, "GET"},
                                  {MHD_OPTION_HANDLER_CALLBACK, (intptr_t) &do_login, "/do_login"},
                                  {MHD_OPTION_END}
                              }, NULL);
    if (!daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}