#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(PAGE), (void*) PAGE, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*upload_data_size != 0) {
        char username[16] = {0};
        char password[16] = {0};

        sscanf(upload_data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_add_response_header(response, "Location", "/admin_page");
            MHD_destroy_response(response);

            return ret;
        }

        *upload_data_size = 0; // Indicate that we are done processing the upload data
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*) "Invalid credentials", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL, &login_handler, NULL, MHD_OPTION_INTERNAL_THREADING_THREADS, 4, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    struct MHD_Daemon *daemon_do_login;

    daemon_do_login = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8889, NULL, NULL, &do_login_handler, NULL, MHD_OPTION_INTERNAL_THREADING_THREADS, 4, MHD_OPTION_END);
    if (NULL == daemon_do_login) {
        MHD_stop_daemon(daemon);
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    MHD_stop_daemon(daemon_do_login);

    return 0;
}