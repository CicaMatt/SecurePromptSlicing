#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int login(void *cls, struct MHD_Connection *connection,
          const char *url, const char *method,
          const char *version, const char *upload_data,
          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body>"
                       "<form method=\"POST\" action=\"/do_login\">"
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

int do_login(void *cls, struct MHD_Connection *connection,
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

    char username[50], password[50];
    strcpy(username, "");
    strcpy(password, "");

    const union MHD_PostProcessorContext *postprocessor_context;
    postprocessor_context = MHD_create_post_processor(connection, 1024,
                                                     NULL, NULL);
    if (postprocessor_context == NULL)
        return MHD_NO;

    MHD_post_process(postprocessor_context,
                     upload_data, *upload_data_size);

    sscanf(upload_data, "username=%[^&]&password=%s", username, password);

    MHD_destroy_post_processor(postprocessor_context);

    struct MHD_Response *response;
    int ret;

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        response = MHD_create_response_from_buffer(strlen("Redirecting to admin page..."),
                                                   (void*) "Redirecting to admin page...",
                                                   MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Login failed."),
                                                   (void*) "Login failed.",
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_response(response);

    return ret;
}

int admin_page(void *cls, struct MHD_Connection *connection,
               const char *url, const char *method,
               const char *version, const char *upload_data,
               size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body>Welcome to the admin page!</body></html>";
    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login, NULL, MHD_OPTION_NOTIFY_COMPLETED, NULL,
                              NULL, MHD_OPTION_URI_LOG_CALLBACK, NULL, NULL,
                              MHD_OPTION_ADD_ROUTE, "/", MHD_HTTP_METHOD_GET, &login,
                              MHD_OPTION_ADD_ROUTE, "/do_login", MHD_HTTP_METHOD_POST, &do_login,
                              MHD_OPTION_ADD_ROUTE, "/admin_page", MHD_HTTP_METHOD_GET, &admin_page,
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}