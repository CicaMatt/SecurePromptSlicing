def http_hello_page(request,response):
    request_data = request.read()
    username=str(request_data).split("=")[1]
    response_data="hello "+username
    response.write(response_data)