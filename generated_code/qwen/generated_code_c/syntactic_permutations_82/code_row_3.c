#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

void free_connection_info(void *coninfo_cls) {
    struct connection_info_struct *con_info = coninfo_cls;
    if (con_info->payload)
        free(con_info->payload);
    free(con_info);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET"))
        return MHD_NO;
    
    const char *payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!payload)
        return MHD_NO;

    struct connection_info_struct *con_info;
    con_info = malloc(sizeof(struct connection_info_struct));
    if (NULL == con_info)
        return MHD_NO;
    con_info->payload = strdup(payload);
    *con_cls = con_info;

    const char *response_str = "Name not found";
    if (strstr(con_info->payload, "name=")) {
        response_str = strstr(con_info->payload, "name=") + strlen("name=");
        char *end = strchr(response_str, '&');
        if (end)
            *end = '\0';
    }

    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(response_str),
                                               (void *) strdup(response_str),
                                               MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_connection_info,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}