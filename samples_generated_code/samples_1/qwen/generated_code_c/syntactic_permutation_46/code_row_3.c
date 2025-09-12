#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *filename;
};

void free_connection_info(void *coninfo_cls) {
    struct connection_info_struct *con_info = coninfo_cls;
    if (NULL != con_info->filename)
        free(con_info->filename);
    free(con_info);
}

int send_file(struct MHD_Connection *connection, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info = *con_cls;
    int fd;
    struct stat file_stat;
    struct MHD_Response *response;

    if (NULL == con_info->filename)
        return MHD_NO;

    fd = open(con_info->filename, O_RDONLY);
    if (-1 == fd)
        return MHD_NO;

    if (0 != fstat(fd, &file_stat)) {
        close(fd);
        return MHD_NO;
    }

    response = MHD_create_response_from_fd(file_stat.st_size, fd);
    if (NULL == response) {
        close(fd);
        return MHD_NO;
    }

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
                         const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    if (*con_cls == NULL) {
        struct connection_info_struct *con_info;
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;

        const char *filename_start = strstr(url, "/img/");
        if (filename_start != url) {
            free(con_info);
            return MHD_NO;
        }

        filename_start += 5; // Move past '/img/'
        con_info->filename = malloc(strlen(filename_start) + 7); // Add 7 for 'images/' and '\0'
        if (NULL == con_info->filename) {
            free(con_info);
            return MHD_NO;
        }
        strcpy(con_info->filename, "images/");
        strcat(con_info->filename, filename_start);

        *con_cls = con_info;

        return MHD_YES;
    }

    return send_file(connection, upload_data, upload_data_size, con_cls);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_connection_info, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}