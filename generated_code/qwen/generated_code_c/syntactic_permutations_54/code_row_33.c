#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *response = "<html><body>"
                           "<form method='post' action='/do_login'>"
                           "Username: <input type='text' name='username'><br>"
                           "Password: <input type='password' name='password'><br>"
                           "<input type='submit' value='Login'>"
                           "</form></body></html>";
    int response_length = strlen(response);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_length, (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int iterated = 0;
    if (!iterated) {
        iterated++;
        return MHD_YES;
    }
    iterated--;

    char username[256] = {0};
    char password[256] = {0};

    const union MHD_PostProcessorContext *post_iterator = MHD_create_post_processor(connection, 1024, NULL, NULL);
    int ret = MHD_post_process(post_iterator, upload_data, *upload_data_size);

    if (ret) {
        const char *key;
        const char *value;

        while (MHD_get_post_processor_context_item(post_iterator, &key, &value)) {
            if (!strcmp(key, "username"))
                strncpy(username, value, sizeof(username) - 1);
            else if (!strcmp(key, "password"))
                strncpy(password, value, sizeof(password) - 1);
        }

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            const char *redirect_url = "/admin_page";
            struct MHD_Response *mhd_response = MHD_create_redirect_response(MHD_HTTP_PERMANENT_REDIRECT, redirect_url);
            ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, mhd_response);
            MHD_destroy_response(mhd_response);
        } else {
            const char *response = "Login failed. Invalid credentials.";
            int response_length = strlen(response);

            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_length, (void *)response, MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, mhd_response);
            MHD_destroy_response(mhd_response);
        }
    }

    MHD_destroy_post_processor(post_iterator);
    return ret;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *response = "<html><body>Welcome to the Admin Page!</body></html>";
    int response_length = strlen(response);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_length, (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT,
                              NULL, NULL,
                              &login_handler, NULL,
                              MHD_OPTION_ARRAY, (const union MHD_OptionItem[]) {
                                      {MHD_OPTION_URI_LOG_CALLBACK, MHD_YES, &printf},
                                      {MHD_OPTION_NOTIFY_COMPLETED, MHD_YES, &MHD_destroy_connection},
                                      {MHD_OPTION_END}
                              },
                              MHD_OPTION_REQUEST_TIMEOUT, (unsigned int) 120,
                              MHD_OPTION_CONNECTION_MEMORY_LIMIT, (size_t) 128 * 1024,
                              MHD_OPTION_QUEUE_POLICY, MHD_QUEUE_STRICT_POLICY,
                              MHD_OPTION_ADD_INTERNAL_ROUTE, "/do_login", &MHD_HTTP_METHOD_POST, &do_login_handler, NULL,
                              MHD_OPTION_ADD_INTERNAL_ROUTE, "/admin_page", &MHD_HTTP_METHOD_GET, &admin_page_handler, NULL,
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}