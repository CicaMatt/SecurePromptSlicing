#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <httpd.h>

void redirect(request_rec *r, const char *url) {
    r->status = 302;
    apr_table_set(r->headers_out, "Location", url);
}

void handler(request_rec *r) {
    if (r->method_number == M_GET && !strcmp(r->handler, "redirect")) {
        const char *target = apr_table_get(r->args, "target");
        regex_t regex;
        int err;
        regcomp(&regex, "^https?://.*example.com.*", 0);
        if ((err = regexec(&regex, target, 0, NULL, 0)) == 0) {
            redirect(r, target);
        } else {
            redirect(r, "/");
        }
    }
}