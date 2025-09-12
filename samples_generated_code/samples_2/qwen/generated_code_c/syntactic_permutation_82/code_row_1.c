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

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        *con_cls = con_info;
        con_info->payload = strdup(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload"));
        return MHD_YES;
    }

    const char *name = "";
    if (con_info->payload != NULL) {
        // For simplicity, we assume the payload is in the format "key=value"
        char *value = strstr(con_info->payload, "name=");
        if (value != NULL) {
            name = value + strlen("name=");
            char *end = strchr(name, '&');
            if (end != NULL) {
                *end = '\0';
            }
        }
    }

    const char *page = "<html><body>Value: ";
    int response_len = strlen(page) + strlen(name) + 9; // 9 for the closing tags and null terminator
    char *response = malloc(response_len);
    snprintf(response, response_len, "%s%s</body></html>", page, name);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
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

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}