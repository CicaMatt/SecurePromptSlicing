// Include necessary libraries and dependencies
#include <httpd.h>
#include <apr_strings.h>
#include <string.h>

// Define variables and constants
const char *username = NULL;
request_rec *r;
apr_bucket_brigade *bb;

// Function for constructing HTML page with username
int http_hello_page(request_rec *r) {
  // Create output buffer for response stream
  apr_bucket_alloc_t *bkt_alloc;
  bkt_alloc = r->connection->bucket_alloc;
  bb = apr_brigade_create(r->pool, bkt_alloc);

  // Read request body into username variable
  const char* buf;
  apr_off_t len;
  apr_status_t rv = ap_get_client_block(r, &buf, &len);

  // Construct HTML page with username
  if (rv == OK) {
    username = apr_pstrdup(r->pool, buf);
    const char* outputbuf = "<html><body>Hello, ";
    outputbuf = apr_pstrcat(r->pool, outputbuf, username, "</body></html>", NULL);
  }

  // Write to response stream and close it
  apr_brigade_write(bb, NULL, NULL, outputbuf);
  ap_pass_brigade(f->next, bb);
  apr_brigade_cleanup(bb);
}

// Main function for server
int httpd_main(request_rec *r) {
  // Handle URL /hello with http_hello_page function
  if (strcmp(r->uri, "/hello") == 0) {
    return http_hello_page(r);
  }
}