#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <microhttpd.h>

#define PORT 8080
#define UPLOAD_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

void mkdir_if_not_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(void *cls, enum MHD_ValueKind kind, const char *key,
                const char *filename, const char *content_type,
                const char *transfer_encoding, const char *data,
                uint64_t off, size_t size) {
    static FILE *fp = NULL;

    if (filename == NULL)
        return MHD_NO;

    if (off == 0) {
        char filepath[MAX_FILENAME_LENGTH];
        snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);
        fp = fopen(filepath, "ab");
        if (fp == NULL) {
            perror("Failed to open file for writing");
            return MHD_NO;
        }
    }

    if (fp != NULL && fwrite(data, 1, size, fp) != size) {
        fclose(fp);
        fp = NULL;
        return MHD_NO;
    }

    if (size == 0 && fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

    return MHD_YES;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    struct MHD_PostProcessor *postprocessor = MHD_create_post_processor(connection, 1024, upload_file, NULL);
    if (postprocessor == NULL)
        return MHD_NO;

    int ret = MHD_YES;
    if (*upload_data_size != 0) {
        if (MHD_post_process(postprocessor, upload_data, *upload_data_size) == MHD_NO) {
            ret = MHD_NO;
        }
        *upload_data_size = 0;
    }

    MHD_destroy_post_processor(postprocessor);
    return ret ? MHD_queue_response(connection, MHD_HTTP_OK, NULL) : MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, NULL);
}

int main() {
    mkdir_if_not_exists(UPLOAD_DIR);

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                  &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}