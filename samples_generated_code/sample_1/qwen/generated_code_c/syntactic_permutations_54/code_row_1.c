#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"POST\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\"><br><input type=\"password\" name=\"password\" placeholder=\"Password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>"

int login(struct MHD_Connection *connection) {
    const char *page = PAGE;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login(struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct MHD_Response *response;
    int ret;

    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        char username[1024], password[1024];
        sscanf(upload_data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", "/admin_page");
            ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        } else {
            const char *message = "<html><body>Invalid credentials</body></html>";
            response = MHD_create_response_from_buffer(strlen(message), (void*) message, MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
        }
        MHD_destroy_response(response);

        *upload_data_size = 0;
    }

    return ret;
}

int admin_page(struct MHD_Connection *connection) {
    const char *message = "<html><body>Welcome to the Admin Page</body></html>";
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(message), (void*) message, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/") == 0)
        return login(connection);
    else if (strcmp(url, "/do_login") == 0)
        return do_login(connection, url, method, version, upload_data, upload_data_size, con_cls);
    else if (strcmp(url, "/admin_page") == 0)
        return admin_page(connection);

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}