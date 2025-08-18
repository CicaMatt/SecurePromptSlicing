#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int login(struct MHD_Connection *connection, const char *url, const char *method) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        const char *page = "<html><body><h1>Login</h1><form action=\"/do_login\" method=\"post\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int do_login(struct MHD_Connection *connection, const char *url, const char *method) {
    if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        const char *page = "<html><body><h1>Login Successful</h1></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int index(struct MHD_Connection *connection, const char *url, const char *method) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/") == 0) {
        const char *page = "<html><body><h1>Welcome to the Index Page</h1></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int user_page(struct MHD_Connection *connection, const char *url, const char *method) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/user") == 0) {
        const char *page = "<html><body><h1>User Page</h1></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int admin_page(struct MHD_Connection *connection, const char *url, const char *method) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/admin") == 0) {
        const char *page = "<html><body><h1>Admin Page</h1></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url,
                         const char *method, const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (login(connection, url, method) == MHD_YES ||
        do_login(connection, url, method) == MHD_YES ||
        index(connection, url, method) == MHD_YES ||
        user_page(connection, url, method) == MHD_YES ||
        admin_page(connection, url, method) == MHD_YES) {
        return MHD_YES;
    }
    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}