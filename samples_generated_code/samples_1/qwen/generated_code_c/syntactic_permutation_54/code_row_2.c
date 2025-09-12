#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *form = "<html><body>"
                   "<form method='post' action='/do_login'>"
                   "Username: <input type='text' name='username'><br>"
                   "Password: <input type='password' name='password'><br>"
                   "<input type='submit' value='Login'>"
                   "</form></body></html>";

const char *admin_page = "<html><body><h1>Welcome, Admin!</h1></body></html>";

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(form), (void*)form, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int post_processed = 0;
    struct MHD_Response *response;
    int ret;

    if (!post_processed) {
        post_processed = 1;
        return MHD_YES;
    }
    post_processed = 0;

    char username[256] = {0};
    char password[256] = {0};

    size_t offset = 0;
    const char *key, *value;
    while (MHD_get_post_processor_value(*con_cls, &offset, &key, &value)) {
        if (strcmp(key, "username") == 0)
            strncpy(username, value, sizeof(username) - 1);
        else if (strcmp(key, "password") == 0)
            strncpy(password, value, sizeof(password) - 1);
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        response = MHD_create_response_from_buffer(strlen(admin_page), (void*)admin_page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Login Failed"), (void*)"Login Failed", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    MHD_destroy_post_processor(*con_cls);
    *con_cls = NULL;
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (*con_cls != NULL) {
        MHD_destroy_post_processor(*con_cls);
        *con_cls = NULL;
    }
}