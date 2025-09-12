#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

void free_connection_info(void *coninfo_cls) {
    struct connection_info_struct *con_info = coninfo_cls;
    if (NULL != con_info->payload)
        free(con_info->payload);
    free(con_info);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info;
    con_info = *con_cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->payload = NULL;
        *con_cls = con_info;

        return MHD_YES;
    }

    const char* payload_param = strchr(url, '?');
    if (payload_param) {
        payload_param++; // Skip the '?'
        size_t param_len = strlen(payload_param);
        con_info->payload = malloc(param_len + 1);
        if (!con_info->payload)
            return MHD_NO;
        strncpy(con_info->payload, payload_param, param_len);
        con_info->payload[param_len] = '\0';
    }

    char *name_value = strstr(con_info->payload, "name=");
    if (name_value) {
        name_value += strlen("name=");
        char *end_of_name = strchr(name_value, '&');
        if (!end_of_name)
            end_of_name = con_info->payload + strlen(con_info->payload);
        size_t name_len = end_of_name - name_value;
        char name[name_len + 1];
        strncpy(name, name_value, name_len);
        name[name_len] = '\0';

        const char *response = name;
        int response_size = strlen(response);

        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
            response_size, (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    const char *not_found = "Name not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
        strlen(not_found), (void*)not_found, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_NOTIFY_COMPLETED, free_connection_info,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}