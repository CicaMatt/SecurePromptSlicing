#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <microhttpd.h>

#define PORT 8888
#define IMAGE_FOLDER "images/"

int send_file(struct MHD_Connection *connection, const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0)
        return MHD_NO;

    FILE *file = fopen(filename, "rb");
    if (!file)
        return MHD_NO;

    struct MHD_Response *response = MHD_create_response_from_callback(
            st.st_size,
            128*1024,
            (MHD_ContentReaderCallback) &MHD_create_file_reader_callback,
            file,
            (MHD_ContentReleaserCallback) &fclose);

    if (!response) {
        fclose(file);
        return MHD_NO;
    }

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

    char filename[256];
    snprintf(filename, sizeof(filename), "%s%s", IMAGE_FOLDER, url+1);

    struct stat st;
    if (stat(filename, &st) == 0 && S_ISREG(st.st_mode))
        return send_file(connection, filename);
    
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}