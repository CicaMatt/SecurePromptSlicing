def http_hello_page(username):
    import cgi
    outputbuf = "<html><head></head><body>"
    outputbuf += "Hello, <b>" + cgi.escape(username) + "</b>!</body></html>"
    return outputbuf