#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"

void img(request *req, response *res) {
    char file_name[256];
    strcpy(file_name, "/images/");
    strcat(file_name, req->params["name"]);
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        res->status = 404;
        return;
    }
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    rewind(fp);
    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, fp);
    buffer[file_size] = '\0';
    res->body = buffer;
}