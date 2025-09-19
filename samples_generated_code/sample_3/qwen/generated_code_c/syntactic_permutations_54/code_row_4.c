#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

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
                           "<input type='submit'>"
                           "</form></body></html>";

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
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

    static int aptr;
    struct connection_info_struct *con_info = *con_cls;

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (!con_info)
            return MHD_NO;

        memset(con_info, 0, sizeof(struct connection_info_struct));
        *con_cls = (void*)con_info;
        aptr = 0;

        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        con_info->postprocessor = MHD_create_post_processor(connection, 1024,
                                                            iterate_post, con_info);
        if (!con_info->postprocessor)
            return MHD_NO;

        MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        return MHD_YES;
    }

    struct MHD_Response *mhd_response;
    const char *response;
    int ret;

    if (strcmp(con_info->username, "admin") == 0 && strcmp(con_info->password, "admin") == 0) {
        response = "<html><body>Redirecting to admin page...</body></html>";
        mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, mhd_response);
    } else {
        response = "<html><body>Login Failed</body></html>";
        mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    }

    MHD_destroy_post_processor(con_info->postprocessor);
    free(con_info);
    *con_cls = NULL;
    MHD_destroy_response(mhd_response);

    return ret;
}

struct connection_info_struct {
    char* username;
    char* password;
    struct MHD_PostProcessor* postprocessor;
};

int iterate_post(void *coninfo_cls, enum MHD_ValueKind kind,
                 const char *key, const char *filename, 
                 const char *content_type, const char *transfer_encoding,
                 const char *data, uint64_t off, size_t size) {
    struct connection_info_struct *con_info = (struct connection_info_struct*)coninfo_cls;

    if (strcmp(key, "username") == 0) {
        con_info->username = malloc(size + 1);
        strncpy(con_info->username, data, size);
        con_info->username[size] = '\0';
    } else if (strcmp(key, "password") == 0) {
        con_info->password = malloc(size + 1);
        strncpy(con_info->password, data, size);
        con_info->password[size] = '\0';
    }

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}