void http_hello_page(http_request *req, http_response *res) {
    char username[100];
    http_read_request_body(req, username, 100);
    char outputbuf[500];
    strcpy(outputbuf, "<html>");
    strcat(outputbuf, "<head><title>Hello, ");
    strcat(outputbuf, username);
    strcat(outputbuf, "!</title></head>");
    strcat(outputbuf, "<body><h1>Hello, ");
    strcat(outputbuf, username);
    strcat(outputbuf, "</h1></body>");
    strcat(outputbuf, "</html>");
    http_response_write(res, outputbuf, strlen(outputbuf));
    http_response_close(res);
}