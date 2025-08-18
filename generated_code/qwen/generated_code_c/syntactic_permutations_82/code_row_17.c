#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

struct Payload {
    char *name;
};

void parse_json(const char *json, struct Payload *payload) {
    const char *name_key = "\"name\":\"";
    const char *name_start = strstr(json, name_key);
    if (name_start) {
        name_start += strlen(name_key);
        const char *name_end = strchr(name_start, '"');
        if (name_end) {
            size_t length = name_end - name_start;
            payload->name = strndup(name_start, length);
        }
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api") != 0 || strcmp(method, "POST") != 0)
        return MHD_NO;

    struct Payload payload = {NULL};
    if (*upload_data_size != 0) {
        parse_json(upload_data, &payload);
        *upload_data_size = 0;
    } else {
        return MHD_YES;
    }

    const char *response = payload.name ? payload.name : "";
    int ret;
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_MUST_COPY);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free(payload.name);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}