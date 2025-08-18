#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <microhttpd.h>

#define PORT 8888

int send_file_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    const char* filename = "index.html"; // The file to send
    int fd;
    struct stat file_stat;
    char *file_content;

    if (strcmp(method, MHD_HTTP_METHOD_GET)) return MHD_NO; // Only handle GET

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return MHD_NO; // File does not exist
    }

    fstat(fd, &file_stat);
    file_content = malloc(file_stat.st_size);
    read(fd, file_content, file_stat.st_size);

    struct MHD_Response *response = MHD_create_response_from_buffer(
            file_stat.st_size, (void*) file_content, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    close(fd);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &send_file_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for keypress

    MHD_stop_daemon(daemon);
    return 0;
}