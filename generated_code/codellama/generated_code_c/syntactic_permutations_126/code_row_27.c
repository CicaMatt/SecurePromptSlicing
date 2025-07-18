char* http_hello_page(char* username) {
    char* html = "<html><head><title>Hello, %s!</title></head>"\
                 "<body><h1>Hello, %s!</h1></body></html>";
    return sprintf(html, username, username);
}