#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>\
<form method='post' action='/do_login'>\
Username: <input type='text' name='username'><br>\
Password: <input type='password' name='password'><br>\
<input type='submit' value='Login'>\
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
    if (strcmp(method, "GET") == 0 && strcmp(url, "/") == 0) {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(PAGE), 
                                                                          (void*) PAGE, 
                                                                          MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        struct FormData *formData = (struct FormData *) *con_cls;
        if (*upload_data_size != 0) {
            formData->username = strstr(upload_data, "username=");
            formData->password = strstr(upload_data, "password=");
            if (formData->username && formData->password) {
                formData->username += strlen("username=");
                formData->password += strlen("password=");
                char *end_username = strchr(formData->username, '&');
                if (end_username) *end_username = '\0';
                char *end_password = strchr(formData->password, '&');
                if (end_password) *end_password = '\0';
            }
            *con_cls = formData;
            *upload_data_size = 0;
            return MHD_YES;
        } else {
            if (formData && strcmp(formData->username, ADMIN_USERNAME) == 0 &&
                strcmp(formData->password, ADMIN_PASSWORD) == 0) {
                struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_redirect(connection, MHD_HTTP_FOUND, "/admin_page");
                MHD_destroy_response(response);
                return ret;
            } else {
                const char *message = "Invalid username or password";
                struct MHD_Response *response = MHD_create_response_from_buffer(strlen(message), 
                                                                              (void*) message, 
                                                                              MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
                MHD_destroy_response(response);
                return ret;
            }
        }
    } else if (strcmp(method, "GET") == 0 && strcmp(url, "/admin_page") == 0) {
        const char *message = "<html><body>Welcome to the admin page</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(message), 
                                                                          (void*) message, 
                                                                          MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}