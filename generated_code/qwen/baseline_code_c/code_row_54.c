#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"POST\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\"><input type=\"password\" name=\"password\" placeholder=\"Password\"><button type=\"submit\">Login</button></form></body></html>"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(PAGE), (void*)PAGE, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        const char *data = upload_data;
        if (*upload_data_size != 0) {
            char username[256] = {0};
            char password[256] = {0};
            sscanf(data, "username=%255[^&]&password=%255s", username, password);

            if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
                struct MHD_Response *response;
                response = MHD_create_response_from_buffer(strlen("<html><body>Admin Page</body></html>"), (void*)"<html><body>Admin Page</body></html>", MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                MHD_destroy_response(response);
                return ret;
            }
        }

        *con_cls = connection;
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*)"Invalid credentials", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}