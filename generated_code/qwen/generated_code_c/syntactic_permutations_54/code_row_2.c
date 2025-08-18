#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, MHD_HTTP_METHOD_GET) != 0)
        return MHD_NO;

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(PAGE), 
                                                                      (void*)PAGE, 
                                                                      MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, MHD_HTTP_METHOD_POST) != 0)
        return MHD_NO;

    char username[256] = {0};
    char password[256] = {0};

    const char* data = upload_data;
    while (*data && *data != '=') data++;
    if (*data == '=') {
        strncpy(username, data + 1, sizeof(username));
        for (char *p = username; *p; p++) if (*p == '&') *p = '\0';
    }

    data += strlen(username) + 2;
    while (*data && *data != '=') data++;
    if (*data == '=') {
        strncpy(password, data + 1, sizeof(password));
        for (char *p = password; *p; p++) if (*p == '&') *p = '\0';
    }

    struct MHD_Response *response;
    int ret;

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        response = MHD_create_response_from_buffer(strlen("<html><body>Redirecting to admin page...</body></html>"), 
                                                  (void*)"<html><body>Redirecting to admin page...</body></html>", 
                                                  MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("<html><body>Invalid username or password</body></html>"), 
                                                  (void*)"<html><body>Invalid username or password</body></html>", 
                                                  MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    }

    MHD_destroy_response(response);

    return ret;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, MHD_HTTP_METHOD_GET) != 0)
        return MHD_NO;

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen("<html><body>Welcome to the admin page</body></html>"), 
                                                                      (void*)"<html><body>Welcome to the admin page</body></html>", 
                                                                      MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    MHD_add_route(daemon, "/do_login", MHD_HTTP_METHOD_POST, &do_login_handler, NULL);
    MHD_add_route(daemon, "/admin_page", MHD_HTTP_METHOD_GET, &admin_page_handler, NULL);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}