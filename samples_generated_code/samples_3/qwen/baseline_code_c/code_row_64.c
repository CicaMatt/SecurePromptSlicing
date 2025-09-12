#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <microhttpd.h>

#define PORT 8080
#define POST_BUFFER_SIZE 512

static int handle_request(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int upload_pos;
    struct connection_info_struct *con_info = *con_cls;

    if (!con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (!con_info) return MHD_NO;
        memset(con_info, 0, sizeof(struct connection_info_struct));
        con_info->memory_data = NULL;
        con_info->memory_data_size = 0;
        *con_cls = (void *)con_info;

        upload_pos = 0;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        char *ptr;

        ptr = realloc(con_info->memory_data, con_info->memory_data_size + *upload_data_size + 1);
        if (!ptr) return MHD_NO;

        con_info->memory_data = ptr;
        memcpy(&(con_info->memory_data[con_info->memory_data_size]), upload_data, *upload_data_size);

        con_info->memory_data_size += *upload_data_size;
        (*upload_data_size) = 0;

        return MHD_YES;
    }

    FILE *fp = fopen("uploaded_file", "wb");
    if (!fp) {
        free(con_info->memory_data);
        free(con_info);
        return MHD_NO;
    }
    fwrite(con_info->memory_data, sizeof(char), con_info->memory_data_size, fp);
    fclose(fp);

    free(con_info->memory_data);
    free(con_info);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen("<html><body>File uploaded</body></html>"),
                                                                     (void *) "<html><body>File uploaded</body></html>",
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);

    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (!daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}

struct connection_info_struct {
    char *memory_data;
    size_t memory_data_size;
};