#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"POST\" action=\"/do_login\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(PAGE), 
                                                                     (void*) PAGE, 
                                                                     MHD_RESPMEM_PERSISTENT);
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

    const char* username = strchr(upload_data, '=') + 1;
    char* password_start = strchr(username, '&') + 9; // skip "&password="
    
    if (!strcmp(username, "admin") && !strcmp(password_start, "admin")) {
        struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    const char* response_msg = "<html><body>Invalid credentials</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_msg), 
                                                                     (void*) response_msg, 
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 
                              8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server started at port 8080\n");

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}