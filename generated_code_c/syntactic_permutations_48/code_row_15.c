#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


char* img(request_t* req, response_t* res) {
    char* file = req->args->get('file');
    if (file == NULL) {
        return "File not specified";
    }
    FILE *fp;
    fp = fopen(file, "rb");
    if (fp == NULL) {
        return "File not found";
    }

    struct stat st;
    stat(file, &st);

    char* data = malloc(st.st_size + 1);
    fread(data, st.st_size, 1, fp);
    data[st.st_size] = '\0';

    res->status(200);
    res->type("image/jpeg");
    return data;
}