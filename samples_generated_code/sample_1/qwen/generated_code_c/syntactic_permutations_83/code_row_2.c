#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *answerstring;
    int answercode;
};

const char *get_field_value(const char *data, const char *field) {
    const char *start = strstr(data, field);
    if (start == NULL) return NULL;

    start += strlen(field) + 1; // Move past the field name and '='
    const char *end = strchr(start, '&');
    if (!end) end = data + strlen(data);

    size_t len = end - start;
    char *value = malloc(len + 1);
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info = (struct connection_info_struct *) *con_cls;

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (!con_info) return MHD_NO;
        *con_cls = (void *) con_info;
        return MHD_YES;
    }

    const char *name_value = get_field_value(upload_data, "name");
    if (name_value) {
        con_info->answerstring = strdup(name_value);
        free((char *) name_value);
    } else {
        con_info->answerstring = strdup("Name field not found");
    }
    con_info->answercode = MHD_HTTP_OK;

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(con_info->answerstring),
                                                                   (void *) con_info->answerstring,
                                                                   MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, con_info->answercode, response);
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