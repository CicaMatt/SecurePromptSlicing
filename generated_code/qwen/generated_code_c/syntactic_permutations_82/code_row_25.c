#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                  const char *url, const char *method,
                                  const char *version, const char *upload_data,
                                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info;
    int ret;

    con_info = (struct connection_info_struct*) *con_cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;

        memset(con_info, 0, sizeof(struct connection_info_struct));

        *con_cls = (void *) con_info;
        return MHD_YES;
    }

    if (strcmp(method, "GET") != 0) {
        free(con_info);
        return MHD_NO;
    }

    const char *payload_param = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (payload_param) {
        con_info->payload = strdup(payload_param);
    } else {
        con_info->payload = NULL;
    }

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(con_info->payload), (void*) con_info->payload, MHD_RESPMEM_MUST_FREE);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    free(con_info);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}