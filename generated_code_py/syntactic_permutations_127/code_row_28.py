def http_hello_page(request,response):
    name=request.read()
    response.write("Hello "+name)