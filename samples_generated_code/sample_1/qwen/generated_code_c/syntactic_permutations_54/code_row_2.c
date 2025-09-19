#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *form_response = 
"<html><body>"
"<form method='post' action='/do_login'>"
"Username: <input type='text' name='username'><br>"
"Password: <input type='password' name='password'><br>"
"<input type='submit' value='Login'>"
"</form></body></html>";

const char *admin_response = 
"<html><body>Welcome to the admin page!</body></html>";

int login_handler(void* cls, struct MHD_Connection* connection,
                  const char* url, const char* method,
                  const char* version, const char* upload_data,
                  size_t* upload_data_size, void** con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(form_response),
                                                                     (void*)form_response,
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void* cls, struct MHD_Connection* connection,
                     const char* url, const char* method,
                     const char* version, const char* upload_data,
                     size_t* upload_data_size, void** con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int first = 1;
    if (first) {
        *con_cls = connection;
        first = 0;
        return MHD_YES;
    }

    first = 1;

    char username[256] = "";
    char password[256] = "";

    sscanf(upload_data, "username=%[^&]&password=%s", username, password);

    struct MHD_Response *response;
    int ret;

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        response = MHD_create_response_from_buffer(strlen(admin_response),
                                                   (void*)admin_response,
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Login Failed"),
                                                   (void*)"Login Failed",
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              request_completed_callback, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}

void request_completed_callback(void* cls, struct MHD_Connection* connection,
                               void** con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL != *con_cls)
        *con_cls = NULL;
}