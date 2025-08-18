#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='POST' action='/do_login'><input type='text' name='username' placeholder='Username'/><br><input type='password' name='password' placeholder='Password'/><br><button type='submit'>Login</button></form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/") == 0 && strcmp(method, MHD_HTTP_METHOD_GET) == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(PAGE), 
                                                   (void *) PAGE, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int do_login(void *cls, struct MHD_Connection *connection,
             const char *url, const char *method,
             const char *version, const char *upload_data,
             size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char* username = NULL;
    const char* password = NULL;

    if (strcmp(method, MHD_HTTP_METHOD_POST) != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        char* content = strndup(upload_data, *upload_data_size);
        username = strstr(content, "username=");
        password = strstr(content, "password=");
        if (username && password) {
            username += strlen("username=");
            password += strlen("password=");
            password[strcspn(password, "&")] = 0;
            if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
                MHD_Redirect(connection, "/admin_page", MHD_HTTP_SEE_OTHER);
            }
        }
        free(content);
        *upload_data_size = 0;
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, &MHD_destroy_response,
                              &do_login, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}