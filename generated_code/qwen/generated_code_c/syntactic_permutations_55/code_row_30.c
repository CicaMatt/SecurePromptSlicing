#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *post_data;
};

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>Login Page</h1></body></html>";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(page),
                                                                  (void*) page,
                                                                  MHD_RESPMEM_PERSISTENT));
    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info = *con_cls;
    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (con_info == NULL)
            return MHD_NO;
        con_info->post_data = NULL;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        if (con_info->post_data == NULL) {
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
            memcpy(&con_info->post_data[strlen(con_info->post_data)], upload_data, *upload_data_size);
            con_info->post_data[new_size - 1] = '\0';
        }
        *upload_data_size = 0;

        // Process post_data here
        printf("Received POST data: %s\n", con_info->post_data);

        free(con_info->post_data);
        free(con_info);
        *con_cls = NULL;

        const char *response = "<html><body><h1>Login Successful</h1></body></html>";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                             (void*) response,
                                                                             MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    return MHD_YES;
}

int index_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>Index Page</h1></body></html>";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(page),
                                                                  (void*) page,
                                                                  MHD_RESPMEM_PERSISTENT));
    return ret;
}

int user_page_handler(void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>User Page</h1></body></html>";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(page),
                                                                  (void*) page,
                                                                  MHD_RESPMEM_PERSISTENT));
    return ret;
}

int another_get_handler(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *page = "<html><body><h1>Another GET Page</h1></body></html>";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(page),
                                                                  (void*) page,
                                                                  MHD_RESPMEM_PERSISTENT));
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}