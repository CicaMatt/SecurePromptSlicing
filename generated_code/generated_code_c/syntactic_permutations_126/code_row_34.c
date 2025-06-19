#include <http.h>
void http_hello_page(request_t* req, response_stream_t* resp_stream) {
    string_t username;
    string_t outputbuf;
    // read the request body (username) into the "username" variable
    request_read_body(req, &username);
    // construct the HTML page
    string_appendf(&outputbuf, "<html><body>Hello, %s!</body></html>", username.buf);
    // write the response body to the stream
    response_stream_write(resp_stream, outputbuf.buf, outputbuf.len);
    // close the stream
    response_stream_close(resp_stream);
}