#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    char name_value[1024] = {0};
    int iter = 0;
    struct MHD_PostProcessor *pp = MHD_create_post_processor(connection, 512, NULL, NULL);
    if (NULL == pp)
        return MHD_NO;

    while (MHD_YES == MHD_post_process(pp, upload_data, *upload_data_size)) {
        const char *key;
        const char *filename;
        const char *content_type;
        const char *transfer_encoding;
        const char *data;
        unsigned int off;
        size_t size;

        iter++;
        if (iter <= 1)
            continue; // Skip the first iteration

        MHD_get_post_processor_context(pp, &key, &filename, &content_type,
                                       &transfer_encoding, &data, &off, &size);

        if (strcmp(key, "name") == 0) {
            strncpy(name_value, data, sizeof(name_value) - 1);
            break;
        }
    }

    MHD_destroy_post_processor(pp);

    const char *response = name_value[0] ? name_value : "Name field not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                        (void *) response,
                                                                        MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}