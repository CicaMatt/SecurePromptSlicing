#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form></body></html>"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char *page = PAGE;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page),
                                               (void *) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int first = 1;
    if (first) {
        first = 0;
        return MHD_YES;
    }

    char username[256] = "";
    char password[256] = "";
    const union MHD_PostProcessorContext *ppc;

    ppc = MHD_create_post_processor(connection, 1024,
                                    NULL, NULL);
    if (MHD_post_process(ppc, upload_data, *upload_data_size)) {
        MHD_post_process(ppc, "", 0);
        struct MHD_Response *response;
        int ret;

        const char* key = "";
        const char* value = "";

        while (MHD_get_post_processor_value(ppc, &key, &value)) {
            if (strcmp(key, "username") == 0) {
                strncpy(username, value, sizeof(username)-1);
            } else if (strcmp(key, "password") == 0) {
                strncpy(password, value, sizeof(password)-1);
            }
        }

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            response = MHD_create_response_from_buffer(strlen("Redirecting to admin page..."),
                                                       (void *) "Redirecting to admin page...", MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", "/admin_page");
            ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
        } else {
            response = MHD_create_response_from_buffer(strlen("Login failed."),
                                                       (void *) "Login failed.", MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
        }

        MHD_destroy_post_processor(ppc);
        MHD_destroy_response(response);
        return ret;
    }
    MHD_destroy_post_processor(ppc);
    return MHD_NO;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body><h1>Welcome to the Admin Page</h1></body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page),
                                               (void *) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    while(1);

    MHD_stop_daemon(daemon);
    return 0;
}