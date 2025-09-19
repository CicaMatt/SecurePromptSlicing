#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *post_data;
};

int login_function(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>Login Page</body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_function(void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *con_info = (struct ConnectionInfoStruct *)*con_cls;

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (con_info == NULL)
            return MHD_NO;
        con_info->post_data = NULL;
        *con_cls = (void *)con_info;
        return MHD_YES;
    }

    if (0 != *upload_data_size) {
        if (!con_info->post_data) {
            con_info->post_data = malloc(*upload_data_size + 1);
            if (con_info->post_data == NULL)
                return MHD_NO;
            memcpy(con_info->post_data, upload_data, *upload_data_size);
            con_info->post_data[*upload_data_size] = '\0';
        } else {
            size_t new_size = strlen(con_info->post_data) + *upload_data_size + 1;
            char *new_post_data = realloc(con_info->post_data, new_size);
            if (new_post_data == NULL)
                return MHD_NO;
            con_info->post_data = new_post_data;
            memcpy(con_info->post_data + strlen(con_info->post_data), upload_data, *upload_data_size);
            con_info->post_data[new_size - 1] = '\0';
        }
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char *page = "<html><body>Do Login Page</body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(con_info->post_data);
    free(con_info);
    *con_cls = NULL;

    return ret;
}

int third_function(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>Third Page</body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int user_page_function(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>User Page</body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int admin_page_function(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    const char *page = "<html><body>Admin Page</body></html>";
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_function, NULL, MHD_OPTION_NOTIFY_COMPLETED, NULL, NULL,
                              MHD_OPTION_HTTPS_MEM_KEY, "server.key",
                              MHD_OPTION_HTTPS_MEM_CERT, "server.pem",
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();
    MHD_stop_daemon(daemon);

    return 0;
}