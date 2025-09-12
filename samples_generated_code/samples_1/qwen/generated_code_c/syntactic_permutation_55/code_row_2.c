#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct ConnectionInfoStruct {
    char *post_data;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *con_info = cls;
    int ret;

    if (NULL == con_info->post_data) {
        con_info->post_data = malloc(1);
        *(con_info->post_data) = '\0';
    }

    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0) {
        if (*upload_data_size != 0) {
            char *new_post_data;
            size_t new_size;

            new_size = strlen(con_info->post_data) + *upload_data_size + 1;
            new_post_data = realloc(con_info->post_data, new_size);
            if (NULL == new_post_data) return MHD_NO;
            con_info->post_data = new_post_data;
            strcat(con_info->post_data, upload_data);
            *upload_data_size = 0;

            return MHD_YES;
        }

        ret = do_login(connection, url, method, version, con_info->post_data);
    } else if (strcmp(method, MHD_HTTP_METHOD_GET) == 0) {
        if (strcmp(url, "/login") == 0) {
            ret = login(connection, url, method, version);
        } else if (strcmp(url, "/user_page") == 0) {
            ret = user_page(connection, url, method, version);
        } else if (strcmp(url, "/admin_page") == 0) {
            ret = admin_page(connection, url, method, version);
        } else {
            ret = MHD_NO;
        }
    } else {
        ret = MHD_NO;
    }

    return ret;
}

int login(struct MHD_Connection *connection,
          const char *url, const char *method,
          const char *version) {
    const char *page = "<html><body><h1>Login</h1></body></html>";
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login(struct MHD_Connection *connection,
             const char *url, const char *method,
             const char *version, char *post_data) {
    const char *page = "<html><body><h1>Logged in</h1></body></html>";
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int user_page(struct MHD_Connection *connection,
              const char *url, const char *method,
              const char *version) {
    const char *page = "<html><body><h1>User Page</h1></body></html>";
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int admin_page(struct MHD_Connection *connection,
               const char *url, const char *method,
               const char *version) {
    const char *page = "<html><body><h1>Admin Page</h1></body></html>";
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;
    struct ConnectionInfoStruct con_info;

    memset(&con_info, 0, sizeof(struct ConnectionInfoStruct));

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void*) &con_info,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    free(con_info.post_data);

    return 0;
}