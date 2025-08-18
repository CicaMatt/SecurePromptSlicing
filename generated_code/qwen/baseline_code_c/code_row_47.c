#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <microhttpd.h>

#define PORT 8888
#define IMAGE_FOLDER "images/"

int send_file_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s%s", IMAGE_FOLDER, url + 1);

    struct stat file_stat;
    if (stat(file_path, &file_stat) == -1 || !S_ISREG(file_stat.st_mode))
        return MHD_NO;

    FILE *file = fopen(file_path, "rb");
    if (!file)
        return MHD_NO;

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (fread(buffer, 1, file_size, file) != file_size) {
        fclose(file);
        free(buffer);
        return MHD_NO;
    }

    fclose(file);

    struct MHD_Response *response = MHD_create_response_from_buffer(file_size, (void *)buffer, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &send_file_handler, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}