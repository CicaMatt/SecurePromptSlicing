#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <microhttpd.h>

#define PORT 8888
#define IMAGE_FOLDER "images"

int send_file(struct MHD_Connection *connection, const char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    if (!fp) return MHD_NO;

    fseek(fp, 0L, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    void *buffer = malloc(file_size);
    fread(buffer, 1, file_size, fp);
    fclose(fp);

    struct MHD_Response *response = MHD_create_response_from_buffer(
        (size_t)file_size,
        buffer,
        MHD_RESPMEM_MUST_FREE
    );

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/%s", IMAGE_FOLDER, url + 1);

    struct stat st;
    if (stat(file_path, &st) == 0 && S_ISREG(st.st_mode)) {
        return send_file(connection, file_path);
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (!daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}