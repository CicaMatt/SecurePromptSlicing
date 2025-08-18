#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='POST' action='/do_login'><input type='text' name='username'/><br/><input type='password' name='password'/><br/><input type='submit' value='Login'/></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(PAGE), (void*) PAGE, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int first_call = 1;
    if (first_call) {
        first_call = 0;
        return MHD_YES;
    }

    first_call = 1;

    const char* username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char* password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (username && strcmp(username, "admin") == 0 &&
        password && strcmp(password, "admin") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*) "Invalid credentials", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);

    return ret;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char* page = "<html><body>Admin Page</body></html>";
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    struct MHD_Queue_Special_Handler_Args queue_special_args;
    queue_special_args.get_con_cls = concls_getter;
    queue_special_args.put_con_cls = concls_putter;

    MHD_add_route(daemon, "/login", MHD_HTTP_METHOD_GET, &login_handler, NULL);
    MHD_add_route(daemon, "/do_login", MHD_HTTP_METHOD_POST, &do_login_handler, NULL);
    MHD_add_route(daemon, "/admin_page", MHD_HTTP_METHOD_GET, &admin_page_handler, NULL);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}