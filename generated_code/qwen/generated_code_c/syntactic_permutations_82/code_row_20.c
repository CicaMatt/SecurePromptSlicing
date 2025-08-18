#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfo {
    char *name;
};

void free_connection_info(void *cls) {
    struct ConnectionInfo *info = cls;
    if (info != NULL) {
        free(info->name);
        free(info);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct ConnectionInfo *info;
    if (*con_cls == NULL) {
        info = malloc(sizeof(struct ConnectionInfo));
        if (!info)
            return MHD_NO;

        const char *name_param = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
        if (name_param) {
            info->name = strdup(name_param);
        } else {
            info->name = NULL;
        }
        *con_cls = info;
        return MHD_YES;
    }

    info = *con_cls;

    int ret;
    const char *page = info->name ? info->name : "Name not provided";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page),
                                                                   (void *) page,
                                                                   MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_NOTIFY_COMPLETED, free_connection_info, NULL,
                              MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}