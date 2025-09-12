#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *post_data;
    size_t post_data_size;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info = cls;
    const char *name_field = "name=";
    const char *value = NULL;

    if (NULL == con_info)
        return MHD_NO; // internal error

    if (0 != strcmp(method, "POST"))
        return MHD_NO;

    if (*upload_data_size != 0) {
        con_info->post_data = realloc(con_info->post_data, con_info->post_data_size + *upload_data_size + 1);
        memcpy(&(con_info->post_data[con_info->post_data_size]), upload_data, *upload_data_size);
        con_info->post_data_size += *upload_data_size;
        con_info->post_data[con_info->post_data_size] = '\0';
        *upload_data_size = 0;

        const char *name_pos = strstr(con_info->post_data, name_field);
        if (name_pos) {
            value = name_pos + strlen(name_field);
            const char *end_of_value = strchr(value, '&');
            if (end_of_value)
                ((char*)value)[end_of_value - value] = '\0';
        }
    }

    if (NULL != value) {
        int ret;
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(value),
                                                                       (void *)strdup(value), MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO; // request not yet complete
}

static void request_completed(void *cls, struct MHD_Connection *connection,
                              void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct connection_info_struct *con_info = *con_cls;

    if (NULL != con_info->post_data)
        free(con_info->post_data);
    free(con_info);
    *con_cls = NULL;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}