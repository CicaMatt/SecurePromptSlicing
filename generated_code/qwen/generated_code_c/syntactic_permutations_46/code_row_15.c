#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *get_image_path(const char *name) {
    static char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);
    return path;
}

int send_file_response(struct MHD_Connection *connection, const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        return MHD_NO;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    void *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    struct MHD_Response *response = MHD_create_response_from_buffer(file_size, buffer, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/img") != 0) {
        return MHD_NO;
    }

    const char *name = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
    if (!name) {
        return MHD_NO;
    }

    const char *file_path = get_image_path(name);
    return send_file_response(connection, file_path);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                               &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}