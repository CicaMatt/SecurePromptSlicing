#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct ConnectionInfo {
    char *payload;
};

void free_connection_info(void *cls) {
    struct ConnectionInfo *coninfo = cls;
    if (NULL != coninfo->payload)
        free(coninfo->payload);
    free(coninfo);
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

    struct ConnectionInfo *coninfo;
    if (*con_cls == NULL) {
        coninfo = malloc(sizeof(struct ConnectionInfo));
        if (NULL == coninfo)
            return MHD_NO;
        coninfo->payload = strdup(payload);
        if (NULL == coninfo->payload) {
            free(coninfo);
            return MHD_NO;
        }
        *con_cls = coninfo;
        return MHD_YES;
    }

    coninfo = *con_cls;
    const char *page = "{\"result\": \"";
    int ret;

    size_t response_size = strlen(page) + strlen(coninfo->payload) + 2; // +2 for the closing quotes and null terminator
    char *response = malloc(response_size);
    snprintf(response, response_size, "%s%s\"}", page, coninfo->payload);

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_connection_info, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);

    return 0;
}