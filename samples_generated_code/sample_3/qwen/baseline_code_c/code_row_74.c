#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <microhttpd.h>

#define PORT 8888
#define IMAGES_FOLDER "images/"

struct MHD_Response *create_file_response(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return NULL;

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    void *content = malloc(fsize + 1);
    fread(content, fsize, 1, fp);
    fclose(fp);

    struct MHD_Response *response = MHD_create_response_from_buffer(fsize, content, MHD_RESPMEM_MUST_FREE);
    return response;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET"))
        return MHD_NO;

    char filename[256];
    snprintf(filename, sizeof(filename), "%s%s", IMAGES_FOLDER, url + 1);

    struct stat st;
    if (stat(filename, &st) != 0 || !S_ISREG(st.st_mode))
        return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, NULL);

    struct MHD_Response *response = create_file_response(filename);
    if (!response)
        return MHD_NO;

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

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