#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct UserCredentials {
    char *username;
    char *password;
};

int login(void *cls, struct MHD_Connection *connection,
          const char *url, const char *method,
          const char *version, const char *upload_data,
          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body>"
                       "<form action=\"/do_login\" method=\"post\">"
                       "Username: <input type=\"text\" name=\"username\"><br>"
                       "Password: <input type=\"password\" name=\"password\"><br>"
                       "<input type=\"submit\" value=\"Submit\">"
                       "</form></body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login(void *cls, struct MHD_Connection *connection,
             const char *url, const char *method,
             const char *version, const char *upload_data,
             size_t *upload_data_size, void **con_cls) {
    static int first_time = 1;

    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    struct UserCredentials *creds;
    if (first_time) {
        creds = malloc(sizeof(struct UserCredentials));
        if (!creds)
            return MHD_NO;
        *con_cls = creds;
        first_time = 0;
        return MHD_YES;
    }

    const char *key, *value;
    size_t key_size, value_size;

    while (MHD_get_post_processor_value(connection, &key, &key_size, &value, &value_size)) {
        if (!creds->username && !strcmp(key, "username")) {
            creds->username = strndup(value, value_size);
        } else if (!creds->password && !strcmp(key, "password")) {
            creds->password = strndup(value, value_size);
        }
    }

    int ret;
    struct MHD_Response *response;

    if (creds->username && creds->password &&
        strcmp(creds->username, "admin") == 0 &&
        strcmp(creds->password, "admin") == 0) {
        response = MHD_create_response_from_buffer(strlen("Redirecting to admin page..."),
                                                   (void*) "Redirecting to admin page...", MHD_RESPMEM_PERSISTENT);
        if (!response)
            return MHD_NO;

        ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
        MHD_add_response_header(response, "Location", "/admin_page");
    } else {
        const char *message = "<html><body>Invalid credentials</body></html>";
        response = MHD_create_response_from_buffer(strlen(message), (void*) message, MHD_RESPMEM_PERSISTENT);
        if (!response)
            return MHD_NO;

        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    free(creds->username);
    free(creds->password);
    free(creds);

    MHD_destroy_response(response);
    return ret;
}

int admin_page(void *cls, struct MHD_Connection *connection,
               const char *url, const char *method,
               const char *version, const char *upload_data,
               size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body>Admin Page</body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login, NULL, MHD_OPTION_NOTIFY_COMPLETED, NULL, NULL,
                              MHD_OPTION_HANDLE_CONNECTIONS_AFTER_UPGRADE, MHD_YES,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}