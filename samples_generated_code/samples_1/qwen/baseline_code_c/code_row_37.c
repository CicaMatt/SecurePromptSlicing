#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form action=\"/do_login\" method=\"post\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\"></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(PAGE), (void*) PAGE, MHD_RESPMEM_PERSISTENT);
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

    static int aptr = 0;
    struct MHD_Response *response;

    if (*upload_data_size != 0) {
        const char* username = strstr(upload_data, "username=");
        const char* password = strstr(upload_data, "password=");

        if (username && password) {
            username += strlen("username=");
            password += strlen("password=");
            char user[100], pass[100];
            strncpy(user, username, strchr(username, '&') - username);
            strncpy(pass, password, strchr(password, '&') - password);

            if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) {
                response = MHD_create_response_from_buffer(strlen("Redirecting..."), (void*) "Redirecting...", MHD_RESPMEM_PERSISTENT);
                MHD_add_response_header(response, "Location", "/admin_page");
                int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
                MHD_destroy_response(response);
                return ret;
            }
        }
        *upload_data_size = 0;
    }

    aptr++;
    *con_cls = &aptr;

    response = MHD_create_response_from_buffer(strlen("Login Failed"), (void*) "Login Failed", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    MHD_add_request_handler(daemon, "/do_login", &do_login_handler, NULL);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}