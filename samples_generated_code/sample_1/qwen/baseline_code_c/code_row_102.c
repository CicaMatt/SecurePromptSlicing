#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    struct MHD_Response *response;
    int ret;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    char name[256] = {0};
    const char *data = upload_data;
    size_t size = *upload_data_size;

    if (size > 0 && strstr(data, "name=")) {
        sscanf(data + strlen("name="), "%255[^&]", name);
    }

    response = MHD_create_response_from_buffer(strlen(name),
                                               (void*) strdup(name),
                                               MHD_RESPMEM_MUST_FREE);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}