void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char* username = NULL;
    while (fgets(buffer, 1024, request)) {
        if (strncmp("username=", buffer, strlen("username=")) == 0) {
            username = buffer + strlen("username=");
        }
    }
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n\r\n");
    fprintf(response, "<!DOCTYPE html><html><body>Hello %s</body></html>\r\n", username);
}