#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *get_field_value(const char *content, const char *field_name) {
    const char *start = strstr(content, field_name);
    if (start == NULL) return NULL;
    start += strlen(field_name) + 1; // move past 'name='
    const char *end = strchr(start, '&');
    size_t length = end ? end - start : strlen(start);
    char *value = strndup(start, length);
    return value;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*upload_data_size != 0) {
        const char *name_value = get_field_value(upload_data, "name");
        if (name_value) {
            struct MHD_Response *response = MHD_create_response_from_buffer(strlen(name_value), (void *) name_value, MHD_RESPMEM_MUST_FREE);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    const char *not_found = "Name field not found";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found), (void *) not_found, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);
    return ret;
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