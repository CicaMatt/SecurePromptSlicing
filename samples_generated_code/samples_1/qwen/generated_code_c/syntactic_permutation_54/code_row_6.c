#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"post\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\"><input type=\"password\" name=\"password\" placeholder=\"Password\"><button type=\"submit\">Login</button></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(PAGE), (void*)PAGE, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int first_call = 1;

    if (first_call) {
        first_call = 0;
        return MHD_YES;
    }

    first_call = 1;

    const char* username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char* password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    struct MHD_Response *response;
    const char* error_message = "<html><body>Invalid username or password</body></html>";
    response = MHD_create_response_from_buffer(strlen(error_message), (void*)error_message, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_HTTPS_MEM_KEY, "server.key",
                              MHD_OPTION_HTTPS_MEM_CERT, "server.crt", MHD_OPTION_END);

    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}