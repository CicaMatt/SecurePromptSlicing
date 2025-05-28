def http_hello_page(request, response):
        inputbuf = request.get_body()
        outputbuf = '<html><body>Hello World!</body></html>'
        response.write(outputbuf)
        response.close()