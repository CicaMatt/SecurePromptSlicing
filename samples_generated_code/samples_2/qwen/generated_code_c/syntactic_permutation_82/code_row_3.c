#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                  const char *url, const char *method,
                                  const char *version, const char *upload_data,
                                  size_t *upload_data_size, void **con_cls) {
    static int first = 1;
    struct connection_info_struct *con_info = cls;

    if (first) {
        first = 0;
        return MHD_YES;
    }

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (!con_info)
            return MHD_NO;
        memset(con_info, 0, sizeof(*con_info));
        *con_cls = (void *)con_info;

        const char* query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
        if (query_string) {
            con_info->payload = strdup(query_string);
        }

        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        *upload_data_size = 0;
        return MHD_YES;
    }

    first = 1;

    const char *name_value = NULL;
    if (con_info->payload) {
        name_value = strstr(con_info->payload, "name=");
        if (name_value) {
            name_value += 5; // Move past 'name='
            char *end = strchr((char*)name_value, '&');
            if (end) {
                *end = '\0';
            }
        }
    }

    const char *response = name_value ? name_value : "Name not found";

    struct MHD_Response *response_struct;
    response_struct = MHD_create_response_from_buffer(strlen(response), 
                                                      (void*)strdup(response),
                                                      MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_struct);

    MHD_destroy_response(response_struct);
    if (con_info->payload)
        free(con_info->payload);
    free(con_info);

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