#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../common/common.h" 

void img(struct http_request *req, struct http_response *res) {
    char *filename = malloc(1024);
    sprintf(filename, "images/%s", req->query_params[0]);
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        send_error(res, HTTP_STATUS_NOT_FOUND, "File not found");
        return;
    }
    char *data = malloc(1024 * 1024);
    int bytes_read = read(fd, data, 1024 * 1024);
    if (bytes_read < 0) {
        send_error(res, HTTP_STATUS_INTERNAL_SERVER_ERROR, "Failed to read file");
        return;
    }
    res->data = data;
    res->status = HTTP_STATUS_OK;
}