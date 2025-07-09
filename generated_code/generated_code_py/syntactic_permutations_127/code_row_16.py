def http_hello_page(request,response):
    user_name = request.read()
    response.write("Hello" + user_name)