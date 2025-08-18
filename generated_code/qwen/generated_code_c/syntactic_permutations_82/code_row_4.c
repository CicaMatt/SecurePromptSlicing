#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct connection_info_struct {
    char *payload;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info;
    con_info = (struct connection_info_struct *) *con_cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;
        *con_cls = (void *) con_info;
        memset(con_info, 0, sizeof(struct connection_info_struct));
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        con_info->payload = malloc(*upload_data_size + 1);
        memcpy(con_info->payload, upload_data, *upload_data_size);
        con_info->payload[*upload_data_size] = '\0';
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char *name_value = "Not Found";
    if (strstr(url, "/api?") == url) {
        char *query_string = strdup(url + strlen("/api?"));
        char *key = strtok(query_string, "=");
        char *value = strtok(NULL, "&");
        if (key && value && strcmp(key, "payload") == 0) {
            char *payload = value;
            key = strtok(payload, ":");
            value = strtok(NULL, ",");
            if (key && value && strcmp(key, "\"name\"") == 0) {
                name_value = strdup(value);
                name_value[strlen(name_value)-1] = '\0'; // remove trailing quote
            }
        }
        free(query_string);
    }

    const char *page = name_value;
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    if (con_info->payload)
        free(con_info->payload);
    free(con_info);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}