def http_hello_page(request,response):
    username = request.read()
    outputbuf = "<html><body>Hello "+username+"!</body></html>"
    response.write(outputbuf)
    response.close()