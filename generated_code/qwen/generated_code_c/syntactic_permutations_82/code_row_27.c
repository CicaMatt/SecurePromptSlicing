#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    const char *name;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info = cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *payload_value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (NULL == payload_value) {
        free(con_info);
        return MHD_NO;
    }

    con_info->name = payload_value;

    int ret;
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(con_info->name),
                                               (void *)con_info->name, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(con_info);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}