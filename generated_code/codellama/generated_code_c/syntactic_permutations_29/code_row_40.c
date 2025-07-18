#include <stdio.h>
#include <stdlib.h>
#include "httplib.h"
#include "regex.h"
int main(void) {
    const char *target = "/";
    httplib_start("0.0.0.0", 80, 1);
    httplib_set_request_handler("/", [](httplib_conn *conn, void *) {
        regex_t reg;
        int res;
        char *url = NULL;
        conn->get_param("target", &url);
        if(url == NULL){
            printf("Url is null");
        } else{
            const char* pattern = ".*example.com";
            res = regcomp(&reg, pattern, 0);
            res = regexec(&reg, url, 0, NULL, 0);
            if (res == REG_NOMATCH) {
                httplib_redirect(conn, "/");
            } else{
                httplib_redirect(conn, url);
            }
        }
    }, NULL);
}