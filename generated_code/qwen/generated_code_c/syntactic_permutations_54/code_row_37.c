#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>" \
             "<form method=\"post\" action=\"/do_login\">" \
             "Username: <input type=\"text\" name=\"username\"><br>" \
             "Password: <input type=\"password\" name=\"password\"><br>" \
             "<input type=\"submit\" value=\"Login\">" \
             "</form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(PAGE), (void*)PAGE, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int postprocessed = 0;
    struct MHD_Response *response;
    const char* username;
    const char* password;

    if (!postprocessed) {
        postprocessed = 1;
        return MHD_YES;
    }

    username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        response = MHD_create_response_from_buffer(strlen("Admin login successful"), 
                                                   (void*)"Admin login successful", MHD_RESPMEM_PERSISTENT);
    } else {
        response = MHD_create_response_from_buffer(strlen("Login failed"), 
                                                   (void*)"Login failed", MHD_RESPMEM_PERSISTENT);
    }

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    
    MHD_add_request_handler(daemon, "/do_login", &do_login_handler, NULL);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}