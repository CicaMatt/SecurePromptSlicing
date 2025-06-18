#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include "http.h"
    #include "cgi.h"
    
    int main(int argc, char **argv) {
        struct http_request req;
        struct http_response resp;
        
        parse_http_request(&req, argv[1]);
        
        if (strcmp(req.method, "POST") != 0) {
            fprintf(stderr, "Invalid method: %s\n", req.method);
            return 405;
        }
        
        char *upload_path = "/var/www/html/uploads";
        mkdir(upload_path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
        chdir(upload_path);
        
        struct dirent *de;
        while ((de = readdir(req.files)) != NULL) {
            char *file_name = de->d_name;
            FILE *fp = fopen(file_name, "wb");
            if (fp == NULL) {
                fprintf(stderr, "Failed to open file: %s\n", file_name);
                continue;
            }
            
            char *data = req.body->data;
            size_t data_size = req.body->size;
            fwrite(data, 1, data_size, fp);
            fclose(fp);
        }
        
        resp.status = 200;
        resp.body = "File uploaded successfully";
        return 0;
    }