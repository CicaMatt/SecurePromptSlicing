#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    const char *username;
};

static int http_hello_page(void *cls, struct MHD_Connection *connection,
                            const char *url, const char *method,
                            const char *version, const char *upload_data,
                            size_t *upload_data_size, void **con_cls) {
    static int first = 1;
    struct ConnectionInfoStruct *con_info;

    if (first) {
        first = 0;
        return MHD_YES;
    }

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (con_info == NULL)
            return MHD_NO;
        *con_cls = (void *)con_info;

        return MHD_YES;
    }

    con_info = *con_cls;

    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*upload_data_size != 0) {
        con_info->username = malloc(*upload_data_size + 1);
        strcpy((char *)con_info->username, upload_data);
        *upload_data_size = 0;
    } else {
        char outputbuf[256];
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body>Hello %s!</body></html>", con_info->username);

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(outputbuf), (void *)outputbuf, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        free((char *)con_info->username);
        free(con_info);

        return ret;
    }

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &http_hello_page, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}