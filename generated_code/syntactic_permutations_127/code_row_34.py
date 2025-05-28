def http_hello_page(request,response):
    request.readline()
    username=request.readline().strip()
    response.write("Hello "+str(username))
    return