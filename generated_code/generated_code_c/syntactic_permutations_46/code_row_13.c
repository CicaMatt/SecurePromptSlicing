#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include "http_status.h"
    #include "request.h"
    #include "response.h"

    void img(struct request *req, struct response *res) {
        if (strcmp(req->method, "GET")) {
            response_set_status_code(res, HTTP_STATUS_METHOD_NOT_ALLOWED);
            return;
        }

        char *img_name = get_query_param("name", req->uri);
        if (img_name == NULL) {
            response_set_status_code(res, HTTP_STATUS_BAD_REQUEST);
            return;
        }

        char path[128];
        snprintf(path, sizeof(path), "images/%s", img_name);
        struct stat st;

        if (stat(path, &st) == -1) {
            response_set_status_code(res, HTTP_STATUS_NOT_FOUND);
            return;
        }

        int fd = open(path, O_RDONLY);
        if (fd == -1) {
            response_set_status_code(res, HTTP_STATUS_INTERNAL_SERVER_ERROR);
            perror("open");
            return;
        }

        response_set_status_code(res, HTTP_STATUS_OK);
        response_set_body_fd(res, fd);
    }