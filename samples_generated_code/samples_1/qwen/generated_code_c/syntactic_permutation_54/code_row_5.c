#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body> \
              <form method=\"post\" action=\"/do_login\"> \
              Username: <input type=\"text\" name=\"username\"><br> \
              Password: <input type=\"password\" name=\"password\"><br> \
              <input type=\"submit\" value=\"Submit\"> \
              </form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

struct FormData {
    char *username;
    char *password;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(PAGE), 
                                                   (void *)PAGE, 
                                                   MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(url, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        struct FormData *data = (struct FormData *)cls;
        if (*upload_data_size != 0) {
            char *key = strtok((char *)upload_data, "=");
            while (key) {
                char *value = strtok(NULL, "&");
                if (strcmp(key, "username") == 0) {
                    data->username = strdup(value);
                } else if (strcmp(key, "password") == 0) {
                    data->password = strdup(value);
                }
                key = strtok(NULL, "=");
            }
            *upload_data_size = 0;
            return MHD_YES;
        } else {
            struct MHD_Response *response;
            char redirect[128];
            if (data->username && strcmp(data->username, ADMIN_USERNAME) == 0 &&
                data->password && strcmp(data->password, ADMIN_PASSWORD) == 0) {
                snprintf(redirect, sizeof(redirect), "http://localhost:8888/admin_page");
                response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
                MHD_add_response_header(response, "Location", redirect);
            } else {
                response = MHD_create_response_from_buffer(strlen("Invalid username or password"), 
                                                           (void *)"Invalid username or password", 
                                                           MHD_RESPMEM_PERSISTENT);
            }
            int ret = MHD_queue_response(connection, data->username && strcmp(data->username, ADMIN_USERNAME) == 0 &&
                                             data->password && strcmp(data->password, ADMIN_PASSWORD) == 0 ? MHD_HTTP_FOUND : MHD_HTTP_UNAUTHORIZED, response);
            free(data->username);
            free(data->password);
            MHD_destroy_response(response);
            return ret;
        }
    } else if (strcmp(url, "/admin_page") == 0 && strcmp(method, "GET") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("<html><body>Welcome Admin!</body></html>"), 
                                                   (void *)"<html><body>Welcome Admin!</body></html>", 
                                                   MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;
    struct FormData data = { NULL, NULL };

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, 
                              NULL, NULL, &answer_to_connection, (void *)&data,
                              MHD_OPTION_END);
    if (!daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}