#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

static int handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {

    if (strcmp(url, "/api") != 0 || strcmp(method, "GET") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info = cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->payload = NULL;
        *con_cls = con_info;

        return MHD_YES;
    }

    const char* payload_param = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (payload_param) {
        con_info->payload = strdup(payload_param);
    } else {
        return MHD_NO;
    }

    struct MHD_Response *response;
    const char *name = NULL;

    // Simplified dictionary parsing for demonstration
    if (con_info->payload && strstr(con_info->payload, "name=")) {
        name = strstr(con_info->payload, "name=");
        name += 5; // move pointer after 'name='
        char *end = strchr(name, '&');
        if (end) *end = '\0'; // truncate at '&' if present
    }

    response = MHD_create_response_from_buffer(strlen(name), (void*)name, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);

    MHD_destroy_response(response);
    free(con_info->payload);
    free(con_info);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}