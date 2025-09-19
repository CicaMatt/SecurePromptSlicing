#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Response {
    const char *data;
    size_t length;
};

const struct MHD_Response *generate_response(const char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    if (!fp)
        return NULL;

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, fp);
    fclose(fp);

    string[fsize] = '\0';

    struct MHD_Response *response = MHD_create_response_from_buffer(
        fsize,
        (void*) string,
        MHD_RESPMEM_MUST_FREE
    );

    return response;
}

int img(void *cls, struct MHD_Connection *connection,
         const char *url, const char *method,
         const char *version, const char *upload_data,
         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *name = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
    if (!name)
        return MHD_NO;

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "./%s", name);

    const struct MHD_Response *response = generate_response(file_path);
    if (!response)
        return MHD_NO;

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(
        MHD_USE_SELECT_INTERNALLY,
        PORT,
        NULL, NULL,
        &img, NULL,
        MHD_OPTION_END
    );

    if (!daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}