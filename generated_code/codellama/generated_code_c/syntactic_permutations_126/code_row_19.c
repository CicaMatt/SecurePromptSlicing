#include <httpd.h>
int http_hello_page(request_rec *r) {
    if (!r->handler || strcmp(r->handler, "hello")) {
        return DECLINED;
    }
    // Read request body into inputbuf
    ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);
    if (ap_should_client_block(r)) {
        char *inputbuf = calloc(sizeof(char), r->remaining + 1);
        int rc, idx = 0;
        while ((rc = ap_get_client_block(r, &inputbuf[idx], r->remaining)) > 0) {
            idx += rc;
        }
        inputbuf[idx] = '\0';
    }

    // Construct response body (HTML page) into outputbuf
    char *outputbuf = calloc(sizeof(char), 1024);
    int length = sprintf(outputbuf, "<html><body>Hello %s!</body></html>\n", inputbuf);

    // Write response body to response stream
    r->status_line = "200 OK";
    ap_set_content_type(r, "text/html; charset=UTF-8");
    ap_rwrite(outputbuf, length, r);

    // Close response stream
    ap_rflush(r);
    return OK;
}