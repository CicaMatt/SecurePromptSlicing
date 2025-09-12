#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <microhttpd.h>

#define PORT 8080
#define UPLOAD_DIR "uploads"

static int post_iterator(void *coninfo_cls, enum MHD_ValueKind kind, const char *key, const char *filename, const char *content_type, const char *transfer_encoding, const char *data, uint64_t off, size_t size) {
    FILE *fp;
    struct connection_info_struct *con_info = (struct connection_info_struct*) coninfo_cls;

    if ((NULL == filename) || (0 == strcmp(filename, ""))) {
        return MHD_NO; 
    }

    fp = fopen(filename, "ab");
    if (!fp) {
        return MHD_NO;
    }

    fwrite(data, size, 1, fp);
    fclose(fp);

    con_info->filename = strdup(filename);
    return MHD_YES;
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct MHD_Response *response;
    int ret;
    struct connection_info_struct *con_info = (struct connection_info_struct*) *con_cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info) return MHD_NO;
        con_info->filename = NULL;
        *con_cls = (void*) con_info;
        return MHD_YES;
    }

    if (0 != strcmp(method, "POST")) {
        response = MHD_create_response_from_buffer(strlen("Invalid request method."), (void*) "Invalid request method.", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (*upload_data_size != 0) {
        aptr = 0;
        MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
        *upload_data_size = 0;

        if (con_info->filename) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, con_info->filename);
            rename(con_info->filename, path);
            free(con_info->filename);
            con_info->filename = NULL;
        }

        response = MHD_create_response_from_buffer(strlen("File uploaded successfully."), (void*) "File uploaded successfully.", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    } else {
        const union MHD_PostProcessorContext *ctx = MHD_create_post_processor(connection, 1024, post_iterator, (void *) con_info);
        if (NULL == ctx) return MHD_NO;
        con_info->postprocessor = ctx;

        response = MHD_create_response_from_buffer(strlen("<html><body><form method='POST' enctype='multipart/form-data'><input type='file' name='file'/><input type='submit'/></form></body></html>"), (void*) "<html><body><form method='POST' enctype='multipart/form-data'><input type='file' name='file'/><input type='submit'/></form></body></html>", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }
}

static void request_completed (void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct connection_info_struct *con_info = (struct connection_info_struct*) *con_cls;

    if (NULL == con_info)
        return;

    if (con_info->filename)
        free(con_info->filename);

    if (con_info->postprocessor)
        MHD_destroy_post_processor(con_info->postprocessor);

    free(con_info);
}

int main() {
    struct MHD_Daemon *daemon;
    mkdir(UPLOAD_DIR, 0755);

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}

struct connection_info_struct {
    char *filename;
    const union MHD_PostProcessorContext *postprocessor;
};