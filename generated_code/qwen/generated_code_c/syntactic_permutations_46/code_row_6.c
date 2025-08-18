#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    const char *filename;
};

int img(void *cls, struct MHD_Connection *connection,
        const char *url, const char *method,
        const char *version, const char *upload_data,
        size_t *upload_data_size, void **con_cls) {

    struct ConnectionInfoStruct *con_info = cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    const char *name = strchr(url, '/') + 1;
    if (!name || !*name) {
        return MHD_NO;
    }
    snprintf(con_info->filename, sizeof("images/") + strlen(name), "images/%s", name);

    FILE *file = fopen(con_info->filename, "rb");
    if (NULL == file)
        return MHD_NO;

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    void *data = malloc(length);
    fread(data, 1, length, file);
    fclose(file);

    struct MHD_Response *response = MHD_create_response_from_buffer(length, data, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &img, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}