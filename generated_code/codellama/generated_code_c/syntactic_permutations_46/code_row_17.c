#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include "mongrel2/mongrel2.h"
    #include "mongrel2/response.h"

    void img(const_mongrel_request req) {
        char* name = req->path; 
        FILE *fp;
        fp = fopen("images/" + name, "r");
        if (fp == NULL) {
            perror("Error opening file"); 
            exit(1); 
        }

        mongrel_response res;
        res.sendfile = fp; 
        return res; 
    }