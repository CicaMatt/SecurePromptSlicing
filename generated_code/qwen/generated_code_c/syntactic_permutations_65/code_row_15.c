#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <microhttpd.h>

#define PORT 8888
#define UPLOAD_DIR "uploads/"

static int post_iterator(void *coninfo_cls, enum MHD_ValueKind kind, const char *key, const char *filename, const char *content_type, const char *transfer_encoding, const char *data, uint64_t off, size_t size) {
    struct connection_info_struct *con_info = (struct connection_info_struct*) coninfo_cls;
    FILE *fp;

    if (NULL == filename)
        return MHD_NO;

    fp = fopen(filename, "a");
    fwrite(data, 1, size, fp);
    fclose(fp);

    con_info->filename = strdup(filename);
    return MHD_YES;
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct connection_info_struct *con_info;

    if (NULL == *con_cls) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->filename = NULL;
        con_info->connection = connection;
        *con_cls = (void*) con_info;

        if (0 != strcmp(method, "POST"))
            return MHD_NO;

        aptr = 0;
        return MHD_YES;
    }

    con_info = (struct connection_info_struct*) *con_cls;

    if (*upload_data_size != 0) {
        int ret;

        ret = MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
        if (ret == MHD_NO)
            return MHD_NO;
        *upload_data_size = 0;

        char path[1024];
        snprintf(path, sizeof(path), "%s%s", UPLOAD_DIR, con_info->filename);

        rename(con_info->filename, path);
        free(con_info->filename);

        return MHD_queue_response(connection, MHD_HTTP_OK, NULL);
    }

    if (con_info->postprocessor != NULL) {
        MHD_destroy_post_processor(con_info->postprocessor);
        con_info->postprocessor = NULL;
    }

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen("<html><body>Upload successful</body></html>"), "<html><body>Upload successful</body></html>", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct stat st;

    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}