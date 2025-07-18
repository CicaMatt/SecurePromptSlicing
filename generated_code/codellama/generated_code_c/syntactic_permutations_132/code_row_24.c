#include <stdio.h>
#include <string.h>
#include "httplib.h"
#include <stdlib.h>
#define FILENAME "hello.html"
void hello(struct httplib_request *req, struct httplib_response *res) {
    char username[100];
    int ret = httplib_get_var(req,"username",username,sizeof(username));
    if (ret < 0) {
        httplib_printf(res, "HTTP/1.1 404 Not Found\r\n");
    } else {
        char *message = malloc(256);
        sprintf(message, "Hello, %s!", username);
        FILE *fp = fopen(FILENAME,"r");
        if (fp == NULL) {
            httplib_printf(res, "HTTP/1.1 404 Not Found\r\n");
        } else {
            char *template = malloc(256);
            while (fgets(template, 256, fp))
                httplib_write(res, template, strlen(template));
            free(template);
        }
        fclose(fp);
    }
}
int main() {
    struct httplib_context *ctx = httplib_start();
    if (ctx != NULL) {
        httplib_set_request_handler(ctx, "/hello/.*", &hello);
        printf("Starting server...\n");
        while (!httplib_stop(ctx))
            sleep(1);
        return 0;
    } else {
        printf("Failed to start server...\n");
        return 1;
    }
}