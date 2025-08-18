#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *get_name_field(const char *payload) {
    const char *start = strstr(payload, "\"name\":\"");
    if (start == NULL) return NULL;
    start += strlen("\"name\":\"");
    const char *end = strchr(start, '"');
    if (end == NULL) return NULL;
    size_t length = end - start;
    char *result = malloc(length + 1);
    strncpy(result, start, length);
    result[length] = '\0';
    return result;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (*upload_data_size != 0) {
        const char *name = get_name_field(upload_data);
        if (name == NULL) {
            free((void *) name);
            return MHD_NO;
        }
        int ret;
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(name), (void *) name, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        free((void *) name);
        return ret;
    }
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}