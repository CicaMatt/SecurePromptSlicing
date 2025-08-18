#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"post\" action=\"/do_login\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;
    
    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(PAGE), (void*)PAGE, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int first_time = 1;
    if (first_time) {
        first_time = 0;
        return MHD_YES;
    }

    char username[256] = {0};
    char password[256] = {0};

    const union MHD_PostProcessorContext *post_proc_ctx = MHD_create_post_processor(connection, 1024, NULL, NULL);
    MHD_post_process(post_proc_ctx, upload_data, *upload_data_size);

    // Extract username and password from form data
    const char* key;
    const char* value;
    while (MHD_post_process_iterate(post_proc_ctx, &key, &value)) {
        if (!strcmp(key, "username"))
            strncpy(username, value, sizeof(username) - 1);
        else if (!strcmp(key, "password"))
            strncpy(password, value, sizeof(password) - 1);
    }
    MHD_destroy_post_processor(post_proc_ctx);

    // Check credentials
    int ret;
    struct MHD_Response *response;
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        response = MHD_create_response_from_buffer(strlen("<html><body>Redirecting...</body></html>"), (void*)"<html><body>Redirecting...</body></html>", MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Location", "/admin_page");
        ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen("<html><body>Invalid credentials</body></html>"), (void*)"<html><body>Invalid credentials</body></html>", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &do_login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 2;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}