#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit'></form></body></html>"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

int login(struct MHD_Connection *connection) {
    const char *page = PAGE;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login(struct MHD_Connection *connection) {
    const char* username = NULL;
    const char* password = NULL;

    struct MHD_Response *response;
    int ret;

    if (MHD_get_connection_values(connection, MHD_POSTDATA_KIND, &username, "username") == NULL ||
        MHD_get_connection_values(connection, MHD_POSTDATA_KIND, &password, "password") == NULL) {
        return MHD_NO;
    }

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        MHD_add_response_header(response, "Location", "/admin_page");
    } else {
        response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*) "Invalid credentials", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_response(response);

    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0)
        return login(connection);
    else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0)
        return do_login(connection);

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}