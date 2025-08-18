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

    char name[256];
    name[0] = '\0';

    const union MHD_PostProcessorContext *post_ctx =
            MHD_create_post_processor(connection, 1024,
                                     answer_to_connection, cls);

    if (post_ctx == NULL)
        return MHD_NO;

    MHD_post_process(post_ctx, upload_data, *upload_data_size);
    MHD_destroy_post_processor(post_ctx);

    const char *key;
    const char *value;
    post_ctx = MHD_create_post_processor(connection, 1024,
                                         answer_to_connection, cls);
    while (MHD_get_post_data(post_ctx, &key, &value)) {
        if (strcmp(key, "name") == 0) {
            strncpy(name, value, sizeof(name) - 1);
            name[sizeof(name) - 1] = '\0';
        }
    }
    MHD_destroy_post_processor(post_ctx);

    if (strlen(name) > 0) {
        response = MHD_create_response_from_buffer(strlen(name), (void *)name,
                                                   MHD_RESPMEM_PERSISTENT);
    } else {
        response = MHD_create_response_from_buffer(3, "N/A",
                                                   MHD_RESPMEM_PERSISTENT);
    }

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