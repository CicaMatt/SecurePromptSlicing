#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <microhttpd.h>

#define PORT 8888
#define UPLOADS_DIR "uploads/"
#define MAX_FILE_SIZE (1024 * 1024 * 5) // 5MB

struct file_info {
    char filename[256];
    FILE* fp;
};

static int upload_file(void* cls, enum MHD_ValueKind kind, const char* key,
                     const char* filename, const char* content_type,
                     const char* transfer_encoding, const char* data,
                     uint64_t off, size_t size) {
    struct file_info *fi = (struct file_info*)cls;
    if (!filename)
        return MHD_YES;

    if (!fi->fp && size > 0) {
        snprintf(fi->filename, sizeof(fi->filename), "%s%s", UPLOADS_DIR, filename);
        fi->fp = fopen(fi->filename, "wb");
        if (!fi->fp)
            return MHD_NO;
    }

    if (size > 0 && fwrite(data, size, 1, fi->fp) != 1) {
        fclose(fi->fp);
        fi->fp = NULL;
        return MHD_NO;
    }
    return MHD_YES;
}

static int answer_to_connection(void* cls, struct MHD_Connection* connection,
                                const char* url, const char* method,
                                const char* version, const char* upload_data,
                                size_t* upload_data_size, void** con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    struct file_info *fi = NULL;
    if (*con_cls == NULL) {
        fi = malloc(sizeof(*fi));
        memset(fi, 0, sizeof(*fi));
        *con_cls = fi;
        aptr = 0;
        return MHD_YES;
    }
    fi = (struct file_info*)*con_cls;

    struct MHD_Response* response;
    int ret;

    if (*upload_data_size != 0) {
        const char* upload_ptr = upload_data + aptr;
        size_t data_size = *upload_data_size - aptr;

        int success = MHD_post_process((struct MHD_PostProcessor*)cls, upload_ptr,
                                       data_size);
        if (!success) {
            response = MHD_create_response_from_buffer(strlen("Failed"), 
                                                      (void*)"Failed", 
                                                      MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
            fclose(fi->fp);
            free(*con_cls);
            *con_cls = NULL;
            return ret;
        }
        aptr += data_size;
    } else {
        response = MHD_create_response_from_buffer(strlen("File uploaded"), 
                                                  (void*)"File uploaded", 
                                                  MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        fclose(fi->fp);
        free(*con_cls);
        *con_cls = NULL;
    }
    return ret;
}

int main() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1)
        mkdir(UPLOADS_DIR, 0755);

    struct MHD_Daemon* daemon;
    struct MHD_PostProcessor* pp;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void*)pp, 
                              MHD_OPTION_NOTIFY_COMPLETED, &MHD_destroy_post_processor,
                              MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started at port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}