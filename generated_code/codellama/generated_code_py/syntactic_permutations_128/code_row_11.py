def http_hello_page(request, response):
    request.read()
    response.write("Hello " + request.user)