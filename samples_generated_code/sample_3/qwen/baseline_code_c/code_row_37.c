#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct FormData {
    const char *username;
    const char *password;
};

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>"
                       "<form method=\"post\" action=\"/do_login\">"
                       "Username: <input type=\"text\" name=\"username\"><br>"
                       "Password: <input type=\"password\" name=\"password\"><br>"
                       "<input type=\"submit\" value=\"Login\">"
                       "</form></body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    static int first_time = 1;
    struct FormData *form_data;
    struct MHD_Response *response;

    if (first_time) {
        first_time = 0;
        return MHD_YES;
    }

    if (*con_cls == NULL) {
        form_data = malloc(sizeof(struct FormData));
        memset(form_data, 0, sizeof(struct FormData));
        *con_cls = form_data;
        return MHD_POST_PROCESSOR_NO_STORE;
    }

    form_data = (struct FormData *)*con_cls;

    if (!strcmp(method, "POST")) {
        const char *key, *value;

        struct MHD_PostProcessor *post_processor =
            MHD_create_post_processor(connection, 1024, NULL, NULL);

        while ((MHD_get_post_processed(post_processor, &key, &value))) {
            if (!strcmp(key, "username"))
                form_data->username = value;
            else if (!strcmp(key, "password"))
                form_data->password = value;
        }

        MHD_destroy_post_processor(post_processor);

        if (form_data->username && form_data->password &&
            !strcmp(form_data->username, "admin") &&
            !strcmp(form_data->password, "admin")) {
            const char *redirect_url = "/admin_page";
            response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", redirect_url);
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_destroy_response(response);
            free(form_data);
            return ret;
        }
    }

    response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*)"Invalid credentials", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    MHD_destroy_response(response);
    free(form_data);

    return ret;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body><h1>Welcome Admin!</h1></body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}