def http_hello_page(outputbuf, inputbuf):
    import html
    outputbuf += "<html><body>Hello, " + html.escape(inputbuf) + "</body></html>"