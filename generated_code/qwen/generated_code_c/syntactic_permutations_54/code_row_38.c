#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"post\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\"><br><input type=\"password\" name=\"password\" placeholder=\"Password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *page = PAGE;

    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        if (*upload_data_size != 0) {
            char *username = strstr(upload_data, "username=");
            char *password = strstr(upload_data, "&password=");
            if (username != NULL && password != NULL) {
                username += strlen("username=");
                password += strlen("&password=");
                if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
                    struct MHD_Response *response;
                    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
                    int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
                    MHD_add_response_header(response, "Location", "/admin_page");
                    MHD_destroy_response(response);
                    return ret;
                }
            }
            *upload_data_size = 0;
        } else {
            aptr++;
            if (aptr == 2) {
                aptr = 0;
                struct MHD_Response *response;
                response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
                MHD_destroy_response(response);
                return ret;
            }
        }
    } else if (strcmp(method, "GET") == 0 && strcmp(url, "/admin_page") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("<html><body>Admin Page</body></html>"), (void*) "<html><body>Admin Page</body></html>", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}