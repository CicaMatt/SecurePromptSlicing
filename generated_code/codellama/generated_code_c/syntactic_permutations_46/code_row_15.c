#include <stdio.h>
    #include <stdlib.h>

    struct file_object {
      FILE *fp;
    };

    struct file_object img(struct http_request *req) {
      char *name = get_param(req->url, "name");
      return open("images/" + name);
    }

    struct file_object open(char *filename) {
      FILE *fp;
      fp = fopen(filename, "r");
      return fp;
    }