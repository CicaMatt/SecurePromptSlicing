#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"POST\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\"><br><input type=\"password\" name=\"password\" placeholder=\"Password\"><br><button type=\"submit\">Login</button></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method, const char *version,
                  const char *upload_data, size_t *upload_data_size, void **con_cls) {
    const char *page = PAGE;
    int ret;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT));
    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method, const char *version,
                     const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int aptr = 0;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    if (!*upload_data_size) {
        return MHD_YES;
    }

    char username[256] = {0};
    char password[256] = {0};

    const char *username_start = strstr(upload_data, "username=");
    const char *password_start = strstr(upload_data, "password=");

    if (username_start && password_start) {
        strncpy(username, username_start + strlen("username="), sizeof(username) - 1);
        strncpy(password, password_start + strlen("password="), sizeof(password) - 1);

        // Remove URL encoding
        for (char *ptr = strchr(username, '&'); ptr; ptr = strchr(ptr, '&')) {
            *ptr = '\0';
        }

        if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen("<html><body>Redirecting to admin page...</body></html>"), 
                                                      (void*)"<html><body>Redirecting to admin page...</body></html>", 
                                                      MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", "/admin_page");
            int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    *upload_data_size = 0;
    const char *errorPage = "<html><body>Login failed</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(errorPage), (void*) errorPage, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_FORBIDDEN, response);
    MHD_destroy_response(response);
    return ret;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method, const char *version,
                       const char *upload_data, size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>Welcome to the Admin Page</body></html>";
    int ret;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT));
    return ret;
}

int main(void) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED, NULL, NULL,
                              MHD_OPTION_HTTPS_MEM_KEY, NULL, // Key
                              MHD_OPTION_HTTPS_MEM_CERT, NULL, // Cert
                              MHD_OPTION_END);

    if (daemon == NULL) {
        return 1;
    }

    struct MHD_UrlHandlerEntry url_handlers[] = {
        {"/", &login_handler, NULL},
        {"/do_login", &do_login_handler, NULL},
        {"/admin_page", &admin_page_handler, NULL},
        {NULL, NULL, NULL}
    };

    for (int i = 0; url_handlers[i].url != NULL; ++i) {
        MHD_add_url_handler(daemon, url_handlers[i].url, url_handlers[i].handler, url_handlers[i].user_data);
    }

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}