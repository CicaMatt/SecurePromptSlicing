def http_hello_page(request,response):
        user = request.read()
        hello = "hello "+user+"\n"
        response.write(hello)