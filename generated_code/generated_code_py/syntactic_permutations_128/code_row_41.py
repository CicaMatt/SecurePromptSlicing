def http_hello_page(request,response):
    request.readline()
    username = request.readline().rstrip('\n')
    response.write("hello" +username)
    return response