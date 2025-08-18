#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "microhttpd.h"

#define PORT 8080

struct connection_info_struct {
    char *payload;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct MHD_Response *response;
    int ret;

    struct connection_info_struct *con_info = (struct connection_info_struct*)*con_cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info) return MHD_NO;
        con_info->payload = NULL;
        *con_cls = (void*)con_info;

        return MHD_YES;
    }

    if (0 != strcmp(method, "GET")) {
        response = MHD_create_response_from_buffer(strlen("Unsupported HTTP method"), 
                                                   strdup("Unsupported HTTP method"), 
                                                   MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (con_info->payload == NULL) {
        const char* payload = strchr(url, '?');
        if (payload != NULL) {
            con_info->payload = strdup(payload + 1); // skip the '?'
        }
    } else {
        if (*upload_data_size != 0) {
            *upload_data_size = 0;
            return MHD_YES;
        }

        char name_value[256] = "Not found";
        if (con_info->payload != NULL) {
            const char* key = "name=";
            const char* value_start = strstr(con_info->payload, key);
            if (value_start != NULL) {
                value_start += strlen(key);
                size_t length = strcspn(value_start, "&");
                strncpy(name_value, value_start, length);
                name_value[length] = '\0';
            }
        }

        response = MHD_create_response_from_buffer(strlen(name_value),
                                                   strdup(name_value),
                                                   MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        free(con_info->payload);
        free(con_info);
        *con_cls = NULL;

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