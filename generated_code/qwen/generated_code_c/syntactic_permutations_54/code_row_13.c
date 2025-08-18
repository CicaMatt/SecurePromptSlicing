#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form></body></html>"

int login(struct MHD_Connection *connection) {
    const char *page = PAGE;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int do_login(struct MHD_Connection *connection) {
    const char* username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char* password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
        MHD_add_response_header(response, "Location", "/admin_page");
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/login") == 0 && strcmp(method, "GET") == 0) {
        return login(connection);
    } else if (strcmp(url, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        return do_login(connection);
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888,
                              NULL, NULL, &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}