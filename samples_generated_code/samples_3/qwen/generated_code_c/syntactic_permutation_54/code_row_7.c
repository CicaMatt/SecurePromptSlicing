#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'><input type='text' name='username' placeholder='Username'/><input type='password' name='password' placeholder='Password'/><button type='submit'>Login</button></form></body></html>"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char *page = PAGE;
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
    if (*con_cls == NULL) {
        *con_cls = malloc(sizeof(int));
        return MHD_YES;
    }

    if (strcmp(method, "POST") == 0) {
        static int aptr;
        const char* username = strstr(upload_data, "username=");
        const char* password = strstr(upload_data, "password=");

        if (username && password) {
            username += strlen("username=");
            password += strlen("password=");
            char* end_of_username = strchr(username, '&');
            if (end_of_username) *end_of_username = '\0';

            char* end_of_password = strchr(password, '&') ? strchr(password, '&') : password + strlen(password);
            if (*end_of_password) *end_of_password = '\0';

            if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
                struct MHD_Response* response = MHD_create_response_from_buffer(strlen("Redirecting..."), (void*) "Redirecting...", MHD_RESPMEM_PERSISTENT);
                MHD_add_response_header(response, "Location", "/admin_page");
                return MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            }
        }

        struct MHD_Response* response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*) "Invalid credentials", MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    free(*con_cls);
    *con_cls = NULL;

    struct MHD_Response* response = MHD_create_response_from_buffer(strlen("Method not allowed"), (void*) "Method not allowed", MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, response);
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char* page = "<html><body><h1>Welcome Admin</h1></body></html>";
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    MHD_add_route_get(daemon, "/admin_page", admin_page_handler, NULL);
    MHD_add_route_post(daemon, "/do_login", do_login_handler, NULL);

    printf("Server running. Press Enter to stop.\n");
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}