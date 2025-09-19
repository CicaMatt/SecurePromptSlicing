#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <microhttpd.h>

#define PORT 8888
#define UPLOAD_DIR "uploads/"

static int handle_request(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int upload_processed = 0;
    FILE *fp;
    const char *filename;

    if (strcmp(method, "POST") != 0)
        return MHD_NO; // Only POST method is handled

    struct MHD_Response *response;
    int ret;

    if (!upload_processed) {
        const char *content_type = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "Content-Type");
        if (NULL == content_type || 0 != strncmp(content_type, "multipart/form-data", 19))
            return MHD_NO; // Not a multipart form

        filename = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "filename");
        if (!filename)
            return MHD_NO;

        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

        fp = fopen(filepath, "wb");
        if (NULL == fp)
            return MHD_NO;

        *con_cls = fp;
        upload_processed = 1;
    } else {
        fp = *con_cls;
        if (*upload_data_size != 0) {
            fwrite(upload_data, 1, *upload_data_size, fp);
            *upload_data_size = 0;
        } else {
            fclose(fp);
            response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            upload_processed = 0;
            return ret;
        }
    }

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;
    mkdir(UPLOAD_DIR, 0755);

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}