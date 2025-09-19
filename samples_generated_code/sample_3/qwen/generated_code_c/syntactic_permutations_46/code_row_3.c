#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888
#define IMAGE_DIR "images/"

struct MHD_Response *handle_img_request(const char *name) {
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s%s", IMAGE_DIR, name);

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        return MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        return MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    struct MHD_Response *response = MHD_create_response_from_buffer(file_size, (void *)buffer, MHD_RESPMEM_MUST_FREE);
    MHD_add_response_header(response, "Content-Type", "image/jpeg");
    return response;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/img") != 0) {
        return MHD_NO;
    }

    const char *name = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
    if (!name) {
        return MHD_NO;
    }

    struct MHD_Response *response = handle_img_request(name);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}