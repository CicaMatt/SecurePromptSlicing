#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *get_name_from_payload(const char *payload) {
    const char *name_field = "name=";
    const char *name_start = strstr(payload, name_field);
    if (name_start != NULL) {
        name_start += strlen(name_field);
        const char *name_end = strchr(name_start, '&');
        int name_length;
        if (name_end != NULL) {
            name_length = name_end - name_start;
        } else {
            name_length = strlen(name_start);
        }
        char *name = malloc(name_length + 1);
        strncpy(name, name_start, name_length);
        name[name_length] = '\0';
        return name;
    }
    return NULL;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*upload_data_size != 0) {
        const char *name = get_name_from_payload(upload_data);
        if (name != NULL) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(name), (void *) name, MHD_RESPMEM_MUST_FREE);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            return ret;
        }
    }
    return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}