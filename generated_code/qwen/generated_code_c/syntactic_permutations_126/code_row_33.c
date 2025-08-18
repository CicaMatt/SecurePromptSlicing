#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int http_hello_page(void *cls, struct MHD_Connection *connection,
                           const char *url, const char *method,
                           const char *version, const char *upload_data,
                           size_t *upload_data_size, void **con_cls) {
    static int upload_ready = 0;
    if (strcmp(url, "/hello") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info = *con_cls;
    if (!con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (!con_info)
            return MHD_NO;
        *con_cls = con_info;
        memset(con_info, 0, sizeof(*con_info));
    }

    if (strcmp(method, "POST") != 0) {
        const char *response = "<html><body>Use POST method to send username</body></html>";
        int ret;
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    if (!upload_ready) {
        upload_ready = 1;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        memcpy(con_info->username, upload_data, *upload_data_size);
        con_info->username[*upload_data_size] = '\0';
        *upload_data_size = 0;
    } else {
        char outputbuf[512];
        snprintf(outputbuf, sizeof(outputbuf), "<html><body>Hello, %s!</body></html>", con_info->username);

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(outputbuf),
                                                                          (void*)outputbuf,
                                                                          MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        free(con_info);
        return ret;
    }

    return MHD_YES;
}

struct connection_info_struct {
    char username[128];
};

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &http_hello_page, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}