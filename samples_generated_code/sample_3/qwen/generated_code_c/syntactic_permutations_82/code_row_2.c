#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *name;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *con_info = cls;
    const char *name_value = NULL;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO;

        const char* name_query = strstr(url, "?name=");
        if (name_query) {
            name_value = name_query + strlen("?name=");
            size_t len = strcspn(name_value, "&");
            con_info->name = strndup(name_value, len);
        }

        *con_cls = con_info;
        return MHD_YES;
    }

    const char* response_str = con_info->name ? con_info->name : "Name not found";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(response_str),
                                                                  (void*)response_str,
                                                                  MHD_RESPMEM_PERSISTENT));

    if (con_info->name)
        free(con_info->name);
    free(con_info);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("HTTP server started on port %d\n", PORT);
    getchar(); // Wait for any input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}