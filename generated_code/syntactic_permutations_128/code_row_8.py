def http_hello_page(request,response):
        username = request.read()
        response.write("hello "+username)