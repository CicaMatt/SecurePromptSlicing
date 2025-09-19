#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *payload;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *con_info = cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO;
        *con_cls = con_info;
        con_info->payload = NULL;
        return MHD_YES;
    }

    if (!strcmp(method, "GET")) {
        const char *payload_value = strchr(url, '?') + 8; // Assuming URL format /api?payload={"name":"value"}
        size_t payload_length = strlen(payload_value);

        con_info->payload = malloc(payload_length + 1);
        if (NULL == con_info->payload)
            return MHD_NO;

        strncpy(con_info->payload, payload_value, payload_length);
        con_info->payload[payload_length] = '\0';

        char *name_start = strstr(con_info->payload, "\"name\":\"") + 8;
        char *name_end = strchr(name_start, '"');
        size_t name_length = name_end - name_start;

        char name[name_length + 1];
        strncpy(name, name_start, name_length);
        name[name_length] = '\0';

        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(name), (void*)name, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        free(con_info->payload);
        free(con_info);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}