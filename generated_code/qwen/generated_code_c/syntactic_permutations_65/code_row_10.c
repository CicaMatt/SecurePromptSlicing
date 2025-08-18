#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <microhttpd.h>

#define PORT 8080
#define UPLOAD_DIR "uploads"

struct connection_info_struct {
    char *post_data;
    size_t post_data_size;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                  const char *url, const char *method,
                                  const char *version, const char *upload_data,
                                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info = *con_cls;
    if (!con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        con_info->post_data = NULL;
        con_info->post_data_size = 0;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        size_t new_size = con_info->post_data_size + *upload_data_size;
        con_info->post_data = realloc(con_info->post_data, new_size);
        memcpy(con_info->post_data + con_info->post_data_size, upload_data, *upload_data_size);
        con_info->post_data_size = new_size;
        *upload_data_size = 0;
        return MHD_YES;
    }

    // Assuming the uploaded file is a PDF and its name is "uploaded.pdf"
    FILE *file = fopen(UPLOAD_DIR "/uploaded.pdf", "wb");
    if (file) {
        fwrite(con_info->post_data, 1, con_info->post_data_size, file);
        fclose(file);
    }

    free(con_info->post_data);
    free(con_info);

    struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    mkdir(UPLOAD_DIR, 0755);

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT,
                                                  NULL, NULL,
                                                  &answer_to_connection, NULL,
                                                  MHD_OPTION_END);
    if (!daemon) return 1;

    printf("Server started on port %d. Press Ctrl+C to stop.\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}