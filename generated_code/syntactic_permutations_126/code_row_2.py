def http_hello_page(username):
    import time, sys
    outputbuf = ""
    outputbuf += "<html><head>"
    outputbuf += "<title>Hello!</title></head><body>"
    outputbuf += "<h1>Hello " + username + "</h1></body></html>"
    return outputbuf