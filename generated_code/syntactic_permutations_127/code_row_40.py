def http_hello_page(request,response):
    request.read() #reads the contents of request
    username = request.get_param('username')
    response.write("Hello"+username)
    return