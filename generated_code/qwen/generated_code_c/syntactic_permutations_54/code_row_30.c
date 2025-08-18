#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form></body></html>"

int login(void *cls, struct MHD_Connection *connection,
          const char *url, const char *method,
          const char *version, const char *upload_data,
          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(PAGE), 
                                               (void*) PAGE, 
                                               MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login(void *cls, struct MHD_Connection *connection,
             const char *url, const char *method,
             const char *version, const char *upload_data,
             size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int first = 1;
    if (first) {
        first = 0;
        return MHD_YES;
    }

    char username[256], password[256];
    char *content_type, *data;
    size_t content_length;
    struct MHD_Response *response;

    content_type = MHD_lookup_connection_value(connection, 
                                                 MHD_HEADER_KIND, 
                                                 "Content-Type");
    if (!content_type || strcmp(content_type, "application/x-www-form-urlencoded") != 0)
        return MHD_NO;

    content_length = *upload_data_size;
    data = malloc(content_length + 1);
    memcpy(data, upload_data, content_length);
    data[content_length] = '\0';

    sscanf(data, "username=%[^&]&password=%s", username, password);

    free(data);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        const char *redirect_url = "/admin_page";
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", redirect_url);
        return MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Invalid credentials"),
                                                   (void*) "Invalid credentials",
                                                   MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
        MHD_destroy_response(response);
        return ret;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &login, NULL, MHD_OPTION_HTTPS_MEM_KEY,
                              "-----BEGIN RSA PRIVATE KEY-----\nMIIEowIBAAKCAQEAqP5Gm6D1v4kVjH1rI5o3XxY2iZpR0zF/3eXuZ5Nw\n"
                              "-----END RSA PRIVATE KEY-----",
                              MHD_OPTION_HTTPS_MEM_CERT,
                              "-----BEGIN CERTIFICATE-----\nMIIDXTCCAkWgAwIBAgIJALrCj4J6q9JGMA0GCSqGSIb3DQEBCwUAMEUxCzAJ\n"
                              "-----END CERTIFICATE-----",
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    struct MHD_UrlHandlerEntry url_handlers[] = {
        {"/", login, NULL},
        {"/do_login", do_login, NULL},
        {"/admin_page", login, NULL}, // Placeholder for admin page
        {NULL, NULL, NULL}
    };

    MHD_add_url_handler(daemon, "/", &login, NULL);
    MHD_add_url_handler(daemon, "/do_login", &do_login, NULL);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}