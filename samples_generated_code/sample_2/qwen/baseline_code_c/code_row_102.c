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

    char *content = NULL;
    size_t content_len = 0;

    struct MHD_Response *response;
    int ret;

    const union MHD_ConnectionInfo *ci = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_MEMORY_POOL);
    if (ci == NULL)
        return MHD_NO;

    struct MHD_PostProcessor *postprocessor = MHD_create_post_processor(connection, 1024, answer_to_connection, &content);
    if (postprocessor == NULL)
        return MHD_NO;

    int more_data = 1;
    while (more_data) {
        more_data = MHD_post_process(postprocessor, upload_data, *upload_data_size);
        upload_data += *upload_data_size;
        *upload_data_size = 0;
    }

    if (content != NULL && strstr(content, "name=") != NULL) {
        char *name_start = strstr(content, "name=");
        name_start += strlen("name=");
        char *name_end = strchr(name_start, '&');
        if (name_end == NULL)
            name_end = content + strlen(content);
        size_t name_len = name_end - name_start;
        char name[name_len + 1];
        strncpy(name, name_start, name_len);
        name[name_len] = '\0';
        response = MHD_create_response_from_buffer(strlen(name), (void*)name, MHD_RESPMEM_MUST_COPY);
    } else {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_post_processor(postprocessor);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
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