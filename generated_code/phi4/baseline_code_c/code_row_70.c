#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <libmicrohttpd.h>

#define PORT 8888
#define UPLOADS_DIR "uploads"

void handle_request(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method, 
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "POST")) {
        const char *page = "<html><body>Upload a file</body></html>";
        struct MHD_Response *response;
        int ret;

        response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return;
    }

    if (*con_cls == NULL) {
        *con_cls = malloc(sizeof(struct MHD_PostProcessor *));
        if (!(*con_cls))
            return;

        struct MHD_PostProcessor *postproc;
        postproc = MHD_create_post_processor(connection, 1024,
                                             upload_file, (void *)(*con_cls));
        *((struct MHD_PostProcessor **) (*con_cls)) = postproc;
    }

    struct MHD_PostProcessor *pp = (struct MHD_PostProcessor *) (*con_cls);

    int ret;
    ret = MHD_process_post_data(pp, *upload_data_size,
                                (unsigned char *) upload_data);
    if (MHD_YES == ret)
        *upload_data_size = 0;
    else if (MHD_NO == ret) {
        MHD_destroy_post_processor(pp);
        free(*con_cls);
        *con_cls = NULL;
    }

    if (*upload_data_size != 0) return;

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen("File uploaded successfully"),
                                               (void *) "File uploaded successfully",
                                               MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    if (*con_cls) {
        free(*con_cls);
        *con_cls = NULL;
    }
}

int upload_file(void *cls, enum MHD_ValueKind kind, const char *key,
                const char *filename, const char *content_type,
                const char *transfer_encoding, const char *data, 
                uint64_t off, size_t size) {
    if (0 != strcmp(key, "file")) return MHD_NO;

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (-1 == fd)
        return MHD_NO;

    write(fd, data, size);
    close(fd);

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT, NULL, NULL,
                              &handle_request, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}
