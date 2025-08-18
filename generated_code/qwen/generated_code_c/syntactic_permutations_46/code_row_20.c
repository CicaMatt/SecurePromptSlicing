#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *name;
};

void free_connection_info(void *coninfo) {
    struct connection_info_struct *cis = coninfo;
    if (NULL != cis->name)
        free(cis->name);
    free(cis);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (NULL == *con_cls) {
        struct connection_info_struct *cis;

        cis = malloc(sizeof(struct connection_info_struct));
        if (NULL == cis)
            return MHD_NO;
        memset(cis, 0, sizeof(struct connection_info_struct));
        *con_cls = (void *)cis;

        if (strcmp(method, "GET") == 0) {
            const char* name_param = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
            if (name_param) {
                cis->name = strdup(name_param);
            }
        }

        return MHD_YES;
    }

    struct connection_info_struct *cis = *con_cls;

    FILE *file;
    char filename[256];
    snprintf(filename, sizeof(filename), "./images/%s", cis->name ? cis->name : "default.jpg");

    file = fopen(filename, "rb");
    if (NULL == file) {
        return MHD_NO;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length);
    if (!buffer) {
        fclose(file);
        return MHD_NO;
    }
    fread(buffer, 1, length, file);
    fclose(file);

    struct MHD_Response *response = MHD_create_response_from_buffer(length, (void*)buffer, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free_connection_info(cis);
    *con_cls = NULL;

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}