#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <microhttpd.h>

#define PORT 8080
#define UPLOAD_DIR "uploads"

static int upload_handler(void *cls, MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int upload_done = 0;
    struct connection_info_struct *con_info = *con_cls;
    const char *filename;
    FILE *fp;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->postprocessor = NULL;
        con_info->connectiontype = POSTPROCESSOR_NONE;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (0 != strcmp(method, "POST"))
        return MHD_NO;

    if (!upload_done) {
        const char *content_type = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, MHD_HTTP_HEADER_CONTENT_TYPE);
        if (NULL == content_type)
            return MHD_NO;
        con_info->postprocessor = MHD_create_post_processor(connection, 1024, file_upload_callback, con_info);
        if (NULL == con_info->postprocessor) {
            free(con_info);
            *con_cls = NULL;
            return MHD_NO;
        }
        upload_done = 1;
    }

    MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
    *upload_data_size = 0;

    if (MHD_is_connection_upgrade(connection))
        return MHD_YES;

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen("File uploaded successfully"), (void*) "File uploaded successfully", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

static void file_upload_callback(void *cls, enum MHD_ValueKind kind, const char *key,
                                 const char *filename, const char *content_type,
                                 const char *transfer_encoding, const char *data,
                                 uint64_t off, size_t size) {
    struct connection_info_struct *con_info = cls;

    if (NULL == filename)
        return;

    if (POSTPROCESSOR_NONE == con_info->connectiontype) {
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);
        con_info->fp = fopen(filepath, "wb");
        if (NULL == con_info->fp)
            return;
        con_info->connectiontype = POSTPROCESSOR_FILEUPLOAD;
    }

    if (POSTPROCESSOR_FILEUPLOAD == con_info->connectiontype) {
        fwrite(data, size, 1, con_info->fp);
    }
}

static void request_completed(void *cls, struct MHD_Connection *connection,
                             void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct connection_info_struct *con_info = *con_cls;
    if (NULL == con_info)
        return;

    if (POSTPROCESSOR_FILEUPLOAD == con_info->connectiontype && NULL != con_info->fp) {
        fclose(con_info->fp);
    }

    if (NULL != con_info->postprocessor)
        MHD_destroy_post_processor(con_info->postprocessor);

    free(con_info);
    *con_cls = NULL;
}

int main() {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &upload_handler, NULL,
                              MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);

    return 0;
}