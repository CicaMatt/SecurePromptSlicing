#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        *con_cls = malloc(*upload_data_size + 1);
        memcpy(*con_cls, upload_data, *upload_data_size);
        ((char *)(*con_cls))[*upload_data_size] = '\0';
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char *name_field = "name=";
    char *data = (char *)*con_cls;
    char *name_pos = strstr(data, name_field);
    if (name_pos != NULL) {
        name_pos += strlen(name_field);
        char *end_of_name = strchr(name_pos, '&');
        int name_len = end_of_name ? end_of_name - name_pos : strlen(name_pos);
        char name[name_len + 1];
        strncpy(name, name_pos, name_len);
        name[name_len] = '\0';

        const char *response = "Name received";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    free(*con_cls);
    *con_cls = NULL;

    const char *error_response = "Name field not found";
    struct MHD_Response *mhd_error_response = MHD_create_response_from_buffer(strlen(error_response), (void *)error_response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_error_response);
    MHD_destroy_response(mhd_error_response);
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