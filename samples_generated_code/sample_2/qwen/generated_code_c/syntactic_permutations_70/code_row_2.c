#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <libmicrohttpd.h>

#define PORT 8888

static int handle_file_upload(void *cls, struct MHD_Connection *connection,
                             const char *upload_data, size_t *upload_data_size,
                             void **con_cls) {
    static int upload_pos;
    FILE *fp;
    const char *filename = "uploaded_file";

    if (*con_cls == NULL) {
        fp = fopen(filename, "wb");
        if (fp == NULL) {
            return MHD_NO;
        }
        *con_cls = fp;
        upload_pos = 0;
        return MHD_YES;
    }

    fp = *con_cls;

    if (*upload_data_size != 0) {
        fwrite(upload_data + upload_pos, 1, *upload_data_size, fp);
        upload_pos += *upload_data_size;
        *upload_data_size = 0;
        return MHD_YES;
    } else {
        fclose(fp);
        const char *response = "File uploaded successfully.";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") == 0)
        return handle_file_upload(cls, connection, upload_data, upload_data_size, con_cls);
    else
        return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}