#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct ConnectionInfoStruct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                 const char *url, const char *method,
                                 const char *version, const char *upload_data,
                                 size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *con_info = cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        con_info->payload = NULL;
        *con_cls = con_info;

        return MHD_YES;
    }
    if (0 != *upload_data_size) {
        if (!con_info->payload)
            con_info->payload = strdup(upload_data);
        else {
            char *new_payload = malloc(strlen(con_info->payload) + strlen(upload_data) + 1);
            strcpy(new_payload, con_info->payload);
            strcat(new_payload, upload_data);
            free(con_info->payload);
            con_info->payload = new_payload;
        }
        *upload_data_size = 0;

        return MHD_YES;
    }

    const char *name_value = NULL;
    if (strcmp(method, "GET") == 0 && strcmp(url, "/api") == 0) {
        const char *payload_param = strchr(url, '?');
        if (payload_param != NULL) {
            payload_param += strlen("?payload=");
            char *end = strchr((char*)payload_param, '&');
            size_t len = end ? (size_t)(end - payload_param) : strlen(payload_param);
            char payload[256];
            strncpy(payload, payload_param, len);
            payload[len] = '\0';

            // Assuming payload is a simple key=value pair
            if (strncmp(payload, "name=", 5) == 0) {
                name_value = payload + 5;
            }
        }
    }

    const char *page = NULL;
    int ret;

    if (name_value != NULL) {
        page = MHD_create_response_from_buffer(strlen(name_value), (void*)name_value, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, page);
    } else {
        page = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, page);
    }

    MHD_destroy_response(page);

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