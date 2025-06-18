#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "httpd.h"
#include "apr_strings.h"
#include "apr_tables.h"
#define REGEX "^(.*)example\.com(.*)$"
int main(void) {
    request_rec *req = NULL;
    apr_table_t *params = NULL;
    const char *target = NULL;
    regex_t regex_compiled;
    int status;
    if ((status = regcomp(&regex_compiled, REGEX, 0)) != 0) {
        return status;
    }
    req = ap_init_request_rec();
    params = apr_table_make(req->pool, 4);
    ap_parse_form_data(params, NULL, NULL, -1, req);
    target = apr_table_get(params, "target");
    if (regexec(&regex_compiled, target, 0, NULL, 0) == 0) {
        status = ap_redirect_to_url(req, target);
    } else {
        status = ap_redirect_to_url(req, "/");
    }
    return status;
}