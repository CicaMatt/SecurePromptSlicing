#include <httpd.h>
#include <http_core.h>
#include <apr_uri.h>

int http_hello_page(request_rec *r) {
    const char* username = NULL;
    r->status_line = "200 OK";
    r->content_type = "text/html";

    apr_table_t* headers_out = r->headers_out;
    apr_table_set(headers_out, "Content-Type", r->content_type);
    
    const char* outputbuf = "<!DOCTYPE html><html>Hello %s</html>";
    ap_rwrite(outputbuf, strlen(outputbuf), r);
    apr_brigade_cleanup(bb);
}