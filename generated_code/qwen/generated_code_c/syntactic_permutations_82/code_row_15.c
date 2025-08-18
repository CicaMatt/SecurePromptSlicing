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
    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    struct ConnectionInfoStruct *con_info;
    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (con_info == NULL)
            return MHD_NO;
        con_info->name = NULL;
        *con_cls = con_info;
        return MHD_YES;
    }

    con_info = *con_cls;

    if (*upload_data_size != 0) {
        con_info->name = realloc(con_info->name, *upload_data_size + 1);
        strcpy(con_info->name, upload_data);
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char *response = con_info->name ? con_info->name : "No name provided";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
            strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

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

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}